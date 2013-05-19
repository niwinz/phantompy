# -*- coding: utf-8 -*-

from .api import library as lib


class Context(object):
    def __init__(self):
        self._ctx_ptr = lib.ph_engine_init()
        self._closed = False

    def close(self):
        assert not self._closed, "Context already closed"
        lib.ph_engine_free(self._ctx_ptr)
        self._closed = True


_context = None

def get_context():
    global _context
    if _context is None:
        _context = Context()

    return _context
