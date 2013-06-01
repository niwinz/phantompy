# -*- coding: utf-8 -*-

import json
import datetime

from .api import library as lib
from . import util



class Context(object):
    def __init__(self):
        self._ctx_ptr = lib.ph_context_init()
        self._cfg = Config()

    @property
    def conf(self):
        """
        Return a :py:class:`Config` instance.
        """

        return self._cfg

    def clear_memory_caches(self):
        """
        Clear all memory used by webkit engine.
        """
        lib.ph_context_clear_memory_cache()

    def get_all_cookies(self):
        """
        Get all available cookies.
        """
        cookies_json = lib.ph_context_get_all_cookies()
        return json.loads(util.force_text(cookies_json))

    def set_cookie(self, name, value, domain, path="/", expires=None):
        """
        Generic method for set cookie to the cookiejar instance of
        WebKit Engine.

        :param str name: cookie name.
        :param str value: cookie value.
        :param str domain: cookie domain.

        :param str path: cookie path (default '/')
        :param path: cookie expires date (this must be datetime, date, timedelta
                     or str type.

        :rtype: None
        """

        cookie = {
            "name": name,
            "value": value,
            "domain": domain,
            "path": path,
        }

        if expires:
            if isinstance(expires, (datetime.datetime, datetime.date)):
                expires = expires.isoformat()
            elif isinstance(expires, (util.string_types)):
                pass
            elif isinstance(expires, (datetime.timedelta,)):
                expires = datetime.datetime.utcnow() + expires
            else:
                raise TypeError("invalid type for expires parameter")

            cookie["expires"] = expires

        cookie_data = json.dumps([cookie])
        lib.ph_context_set_cookies(util.force_bytes(cookie_data))

    def set_cookies(self, cookies):
        """
        Set a list of cookies.
        """
        for cookie in cookies:
            self.set_cookie(**cookie)

    def clear_cookies(self):
        """
        Clear all cookies.
        """
        lib.ph_context_clear_cookies()


class Config(object):
    """
    WebKit engine configuration interface.

    This class should onlu be accessed throught :py:class:`Context`
    instance and can not be instanciated as is.

    This config interface exposes these properties:

     * 'load_images' (bool)
     * 'javascript' (bool)
     * 'dns_prefetching' (bool)
     * 'plugins' (bool)
     * 'private_browsing' (bool)
     * 'offline_storage_db' (bool)
     * 'offline_storage_quota' (int)
     * 'frame_flattening' (bool)
     * 'local_storage' (boo)

     And some additional methods:
     """

    _conf_enum = (
        (1, 'load_images', bool,),
        (2, 'javascript', bool,),
        (3, 'dns_prefetching', bool,),
        (4, 'plugins', bool,),
        (5, 'private_browsing', bool,),
        (6, 'offline_storage_db', bool,),
        (7, 'offline_storage_quota', int,),
        (8, 'frame_flattening', bool,),
        (9, 'local_storage', bool,),
    )

    def __new__(cls):
        def _make_getter(key, _type):
            def getter(self):
                if _type == bool:
                    return  _type(lib.ph_context_get_boolean_config(key))
                elif _type == int:
                    return _type(lib.ph_context_get_int_config(key))

            return getter

        def _make_setter(key, _type):
            def setter(self, value):
                if _type == int:
                    lib.ph_context_set_int_config(key, int(value))
                elif _type == bool:
                    lib.ph_context_set_boolean_config(key, int(value))

            return setter

        for key, name, _type in cls._conf_enum:
            getter = _make_getter(key, _type)
            setter = _make_setter(key, _type)
            setattr(cls, name, property(getter, setter))

        return super(Config, cls).__new__(cls)

    def set_object_cache_capacity(self, min_dead_capacity, max_dead, total_capacity):
        """
        Set webkit object cache capacity.
        """
        lib.ph_context_set_object_cache_capacity(min_dead_capacity, max_dead, total_capacity)

    def set_max_pages_in_cache(self, num):
        """
        Set webkit page number to maintain in cache.
        """
        lib.ph_context_set_max_pages_in_cache(num)


_context = None

def context():
    """
    Get or create instance of context (singleton).
    """
    global _context
    if _context is None:
        _context = Context()

    return _context

def destroy_context():
    """
    Destroy context singleton instance.
    """
    global _context
    if _context:
        lib.ph_context_free()
        _context = None
