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
    library.ph_engine_init.argtypes = []
    library.ph_engine_init.restype = ctypes.c_void_p

    library.ph_engine_free.argtypes = [ctypes.c_void_p]
    library.ph_engine_free.restype = None

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

except AttributeError:
    raise ImportError('shared library not found or incompatible')
except (OSError, IOError):
    raise ImportError('shared library not found.\n'
                      'you probably had not installed library.\n')
