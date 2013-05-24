# -*- coding: utf-8 -*-

import ctypes
import ctypes.util
import os
import json

def load_library():
    libpath = ctypes.util.find_library('phantompy')
    libssh = ctypes.CDLL(libpath)
    return libssh

try:
    _library = load_library()
    # Context methods
    _library.ph_context_init.argtypes = []
    _library.ph_context_init.restype = ctypes.c_void_p

    _library.ph_context_free.argtypes = [ctypes.c_void_p]
    _library.ph_context_free.restype = None

    _library.ph_context_clear_memory_cache.argtypes = []
    _library.ph_context_clear_memory_cache.restype = None

    _library.ph_context_set_object_cache_capacity.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_int]
    _library.ph_context_set_object_cache_capacity.restype = None

    _library.ph_context_set_max_pages_in_cache.argtypes = [ctypes.c_int]
    _library.ph_context_set_max_pages_in_cache.restype = None

    # Page methods
    _library.ph_page_create.argtypes = []
    _library.ph_page_create.restype = ctypes.c_void_p

    _library.ph_page_set_viewpoint_size.argtypes = [ctypes.c_void_p, ctypes.c_int, ctypes.c_int]
    _library.ph_page_set_viewpoint_size.restype = None

    _library.ph_page_free.argtypes = [ctypes.c_void_p]
    _library.ph_page_free.restype = None

    _library.ph_page_load.argtypes = [ctypes.c_void_p, ctypes.c_char_p]
    _library.ph_page_load.restype = ctypes.c_int

    _library.ph_page_is_loaded.argtypes = [ctypes.c_void_p]
    _library.ph_page_is_loaded.restype = ctypes.c_int

    _library.ph_page_cookies.argtypes = [ctypes.c_void_p]
    _library.ph_page_cookies.restype = ctypes.c_char_p

    _library.ph_page_requested_urls.argtypes = [ctypes.c_void_p]
    _library.ph_page_requested_urls.restype = ctypes.c_char_p

    # Frame methods
    _library.ph_page_main_frame.argtypes = [ctypes.c_void_p]
    _library.ph_page_main_frame.restype = ctypes.c_void_p

    _library.ph_frame_free.argtypes = [ctypes.c_void_p]
    _library.ph_frame_free.restype = None

    _library.ph_frame_to_html.argtypes = [ctypes.c_void_p]
    _library.ph_frame_to_html.restype = ctypes.c_char_p

    _library.ph_frame_evaluate_javascript.argtypes = [ctypes.c_void_p, ctypes.c_char_p]
    _library.ph_frame_evaluate_javascript.restype = ctypes.c_char_p

    # Image methods
    _library.ph_frame_capture_image.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_int]
    _library.ph_frame_capture_image.restype = ctypes.c_void_p

    _library.ph_image_get_size.argtypes = [ctypes.c_void_p]
    _library.ph_image_get_size.restype = ctypes.c_longlong

    _library.ph_image_get_format.argtypes = [ctypes.c_void_p]
    _library.ph_image_get_format.restype = ctypes.c_char_p

    _library.ph_image_free.argtypes = [ctypes.c_void_p]
    _library.ph_image_free.restype = None

    _library.ph_image_get_bytes.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_longlong]
    _library.ph_image_get_bytes.restype = None

    # Web Element Collection methods

    _library.ph_webcollection_size.argtypes = [ctypes.c_void_p]
    _library.ph_webcollection_size.restype = ctypes.c_int

    _library.ph_webcollection_get_webelement.argtypes = [ctypes.c_void_p, ctypes.c_int]
    _library.ph_webcollection_get_webelement.restype = ctypes.c_void_p

    _library.ph_webcollection_free.argtypes = [ctypes.c_void_p]
    _library.ph_webcollection_free.restype = None

    # Web Element methods
    _library.ph_frame_find_first.argtypes = [ctypes.c_void_p, ctypes.c_char_p]
    _library.ph_frame_find_first.restype = ctypes.c_void_p

    _library.ph_frame_find_all.argtypes = [ctypes.c_void_p, ctypes.c_char_p]
    _library.ph_frame_find_all.restype = ctypes.c_void_p

    _library.ph_webelement_free.argtypes = [ctypes.c_void_p]
    _library.ph_webelement_free.restype = None

    _library.ph_webelement_tag_name.argtypes = [ctypes.c_void_p]
    _library.ph_webelement_tag_name.restype = ctypes.c_char_p

    _library.ph_webelement_inner_html.argtypes = [ctypes.c_void_p]
    _library.ph_webelement_inner_html.restype = ctypes.c_char_p

    _library.ph_webelement_inner_text.argtypes = [ctypes.c_void_p]
    _library.ph_webelement_inner_text.restype = ctypes.c_char_p

    _library.ph_webelement_find_all.argtypes = [ctypes.c_void_p, ctypes.c_char_p]
    _library.ph_webelement_find_all.restype = ctypes.c_void_p

    #_library.ph_webelement_has_class.argtypes = [ctypes.c_void_p, ctypes.c_char_p]
    #_library.ph_webelement_has_class.restype = ctypes.c_int

    #_library.ph_webelement_has_attr.argtypes = [ctypes.c_void_p, ctypes.c_char_p]
    #_library.ph_webelement_has_attr.restype = ctypes.c_int

    #_library.ph_webelement_has_attrs.argtypes = [ctypes.c_void_p]
    #_library.ph_webelement_has_attrs.restype = ctypes.c_int

    _library.ph_webelement_is_null.argtypes = [ctypes.c_void_p]
    _library.ph_webelement_is_null.restype = ctypes.c_int

except AttributeError:
    raise ImportError('shared library not found or incompatible')
except (OSError, IOError):
    raise ImportError('shared library not found.\n'
                      'you probably had not installed library.\n')


class ExternLibraryInterface(object):
    def __init__(self, lib):
        self._clib = lib

    def ph_image_get_bytes(self, ptr, size):
        blob = ctypes.create_string_buffer(size)
        self._clib.ph_image_get_bytes(ptr, ctypes.byref(blob), size)
        return blob.raw

    def __getattr__(self, name):
        return getattr(self._clib, name)

library = ExternLibraryInterface(_library)
