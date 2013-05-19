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
    library = load_library()
    # Context methods
    library.ph_engine_init.argtypes = []
    library.ph_engine_init.restype = ctypes.c_void_p

    library.ph_engine_free.argtypes = [ctypes.c_void_p]
    library.ph_engine_free.restype = None

    # Page methods
    library.ph_page_create.argtypes = []
    library.ph_page_create.restype = ctypes.c_void_p

    library.ph_page_set_viewpoint_size.argtypes = [ctypes.c_void_p, ctypes.c_int, ctypes.c_int]
    library.ph_page_set_viewpoint_size.restype = None

    library.ph_page_free.argtypes = [ctypes.c_void_p]
    library.ph_page_free.restype = None

    library.ph_page_load.argtypes = [ctypes.c_void_p, ctypes.c_char_p]
    library.ph_page_load.restype = ctypes.c_int

    library.ph_page_is_loaded.argtypes = [ctypes.c_void_p]
    library.ph_page_is_loaded.restype = ctypes.c_int

    library.ph_page_to_html.argtypes = [ctypes.c_void_p]
    library.ph_page_to_html.restype = ctypes.c_char_p

    library.ph_page_evaluate_javascript.argtypes = [ctypes.c_void_p, ctypes.c_char_p]
    library.ph_page_evaluate_javascript.restype = ctypes.c_char_p

    # Image methods
    library.ph_page_capture_image.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_int]
    library.ph_page_capture_image.restype = ctypes.c_void_p

    library.ph_image_get_size.argtypes = [ctypes.c_void_p]
    library.ph_image_get_size.restype = ctypes.c_longlong

    library.ph_image_get_format.argtypes = [ctypes.c_void_p]
    library.ph_image_get_format.restype = ctypes.c_char_p

    library.ph_image_free.argtypes = [ctypes.c_void_p]
    library.ph_image_free.restype = None

    library.ph_image_get_bytes.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_longlong]
    library.ph_image_get_bytes.restype = None

    # Web Element methods
    library.ph_page_find_first.argtypes = [ctypes.c_void_p, ctypes.c_char_p]
    library.ph_page_find_first.restype = ctypes.c_void_p

    library.ph_webelement_free.argtypes = [ctypes.c_void_p]
    library.ph_webelement_free.restype = None

    library.ph_webelement_tag_name.argtypes = [ctypes.c_void_p]
    library.ph_webelement_tag_name.restype = ctypes.c_char_p

    library.ph_webelement_inner_html.argtypes = [ctypes.c_void_p]
    library.ph_webelement_inner_html.restype = ctypes.c_char_p

    library.ph_webelement_inner_text.argtypes = [ctypes.c_void_p]
    library.ph_webelement_inner_text.restype = ctypes.c_char_p

    #library.ph_webelement_has_class.argtypes = [ctypes.c_void_p, ctypes.c_char_p]
    #library.ph_webelement_has_class.restype = ctypes.c_int

    #library.ph_webelement_has_attr.argtypes = [ctypes.c_void_p, ctypes.c_char_p]
    #library.ph_webelement_has_attr.restype = ctypes.c_int

    #library.ph_webelement_has_attrs.argtypes = [ctypes.c_void_p]
    #library.ph_webelement_has_attrs.restype = ctypes.c_int

    library.ph_webelement_is_null.argtypes = [ctypes.c_void_p]
    library.ph_webelement_is_null.restype = ctypes.c_int

except AttributeError:
    raise ImportError('shared library not found or incompatible')
except (OSError, IOError):
    raise ImportError('shared library not found.\n'
                      'you probably had not installed library.\n')
