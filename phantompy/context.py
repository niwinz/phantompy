# -*- coding: utf-8 -*-

from .api import library as lib


class Context(object):
    def __init__(self):
        self._ctx_ptr = lib.ph_context_init()

    def clear_memory_caches(self):
        lib.ph_context_clear_memory_cache()

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
        lib.ph_context_free(_context._ctx_ptr)
        _context = None
