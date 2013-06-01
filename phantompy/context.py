# -*- coding: utf-8 -*-

import json
from .api import library as lib
from . import util


class Context(object):
    def __init__(self):
        self._ctx_ptr = lib.ph_context_init()
        self._cfg = Config()

    @property
    def conf(self):
        return self._cfg

    def clear_memory_caches(self):
        lib.ph_context_clear_memory_cache()

    def get_all_cookies(self):
        cookies_json = lib.ph_context_get_all_cookies()
        return json.loads(util.force_text(cookies_json))



class Config(object):
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
        lib.ph_context_set_object_cache_capacity(min_dead_capacity, max_dead, total_capacity)

    def set_max_pages_in_cache(self, num):
        lib.ph_context_set_max_pages_in_cache(num)


_context = None

def context():
    global _context
    if _context is None:
        _context = Context()

    return _context

def destroy_context():
    global _context
    if _context:
        lib.ph_context_free()
        _context = None
