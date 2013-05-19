# -*- coding: utf-8 -*-

from .api import library as lib
from .api import ctypes


class WebElement(object):
    def __init__(self, el_ptr, page):
        self._el_ptr = el_ptr
        self._page = page
        self._closed = False

        # Setup tagname
        tagname = lib.ph_webelement_tag_name(el_ptr)
        self._tag_name = tagname.decode("utf-8")

    def __repr__(self):
        return "<WebElement <{0}> >".format(self.name)

    @property
    def ptr(self):
        assert not self._page.is_closed(), "Page closed"
        return self._el_ptr

    def __del__(self):
        lib.ph_webelement_free(self.ptr)

    @property
    def name(self):
        return self._tag_name

    def inner_html(self):
        result = lib.ph_webelement_inner_html(self.ptr)
        return result.decode("utf-8")

    def inner_text(self):
        result = lib.ph_webelement_inner_text(self.ptr)
        return result.decode("utf-8")

    def is_none(self):
        result = lib.ph_webelement_is_null(self.ptr)
        return True if result == 0 else False
