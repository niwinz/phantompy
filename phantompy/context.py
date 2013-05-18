# -*- coding: utf-8 -*-

from .api import library as lib

class Context(object):
    def __init__(self):
        self._ctx_ptr = lib.ph_engine_init()

    def __del__(self):
        lib.ph_engine_free(self._ctx_ptr)

    @property
    def ptr(self):
        return self._ctx_ptr
