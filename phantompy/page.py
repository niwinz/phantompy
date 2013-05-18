# -*- coding: utf-8 -*-

from ._library import library as lib
from . import context


class Page(object):
    def __init__(self, url, size=(1280, 768), ctx=None):
        if ctx is None:
            ctx = context.Context()

        self._context = ctx
        self._url = url
        self._loaded = False
        self._size = size

        self._page_ptr = lib.ph_page_create()

    def load(self):
        if self._loaded:
            raise RuntimeError("Page already loaded")

        lib.ph_page_set_viewpoint_size(self._page_ptr,
                                        self._size[0],
                                        self._size[1])

        result = lib.ph_page_load(self._page_ptr, self._url.encode('utf-8'))
        if result != 0:
            raise RuntimeError("Error loading page")

    def to_html(self):
        return lib.ph_page_to_html(self._page_ptr)
