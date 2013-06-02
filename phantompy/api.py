# -*- coding: utf-8 -*-

import ctypes
import ctypes.util
from ctypes import *
import warnings
import os
import json

def load_library():
    cwd = os.path.dirname(os.path.abspath(__file__))
    libdir = os.path.join(cwd, "_phantompy.so")
    return ctypes.CDLL(libdir)


try:
    _library = load_library()
    # Context methods
    _library.ph_context_init.argtypes = []
    _library.ph_context_init.restype = c_void_p

    _library.ph_context_free.argtypes = []
    _library.ph_context_free.restype = None

    _library.ph_context_clear_cookies.argtypes = []
    _library.ph_context_clear_cookies.restype = None

    _library.ph_context_clear_memory_cache.argtypes = []
    _library.ph_context_clear_memory_cache.restype = None

    _library.ph_context_set_object_cache_capacity.argtypes = [c_int, c_int, c_int]
    _library.ph_context_set_object_cache_capacity.restype = None

    _library.ph_context_set_max_pages_in_cache.argtypes = [c_int]
    _library.ph_context_set_max_pages_in_cache.restype = None

    _library.ph_context_set_boolean_config.argtypes = [c_int, c_int]
    _library.ph_context_set_boolean_config.restype = None
    _library.ph_context_set_int_config.argtypes = [c_int, c_int]
    _library.ph_context_set_int_config.restype = None
    _library.ph_context_get_boolean_config.argtypes = [c_int]
    _library.ph_context_get_boolean_config.restype = c_int
    _library.ph_context_get_int_config.argtypes = [c_int]
    _library.ph_context_get_int_config.restype = c_int

    _library.ph_context_get_all_cookies.argtypes = []
    _library.ph_context_get_all_cookies.restype = c_void_p
    _library.ph_context_get_all_cookies._char_ptr = True

    _library.ph_context_set_cookies.argtypes = [c_char_p]
    _library.ph_context_set_cookies.restype = None

    # Page methods
    _library.ph_page_create.argtypes = []
    _library.ph_page_create.restype = c_void_p

    _library.ph_page_set_viewpoint_size.argtypes = [c_void_p, c_int, c_int]
    _library.ph_page_set_viewpoint_size.restype = None

    _library.ph_page_free.argtypes = [c_void_p]
    _library.ph_page_free.restype = None

    _library.ph_page_load.argtypes = [c_void_p, c_char_p]
    _library.ph_page_load.restype = c_int

    _library.ph_page_is_loaded.argtypes = [c_void_p]
    _library.ph_page_is_loaded.restype = c_int

    _library.ph_page_get_reply_by_url.argtypes = [c_void_p, c_char_p]
    _library.ph_page_get_reply_by_url.restype = c_void_p
    _library.ph_page_get_reply_by_url._char_ptr = True

    _library.ph_page_get_cookies.argtypes = [c_void_p]
    _library.ph_page_get_cookies.restype = c_void_p
    _library.ph_page_get_cookies._char_ptr = True

    _library.ph_page_get_requested_urls.argtypes = [c_void_p]
    _library.ph_page_get_requested_urls.restype = c_void_p
    _library.ph_page_get_requested_urls._char_ptr = True

    _library.ph_page_go_back.argtypes = [c_void_p]
    _library.ph_page_go_back.restype = None

    _library.ph_page_go_forward.argtypes = [c_void_p]
    _library.ph_page_go_forward.restype = None

    # Frame methods
    _library.ph_page_main_frame.argtypes = [c_void_p]
    _library.ph_page_main_frame.restype = c_void_p

    _library.ph_frame_free.argtypes = [c_void_p]
    _library.ph_frame_free.restype = None

    _library.ph_frame_to_html.argtypes = [c_void_p]
    _library.ph_frame_to_html.restype = c_void_p
    _library.ph_frame_to_html._char_ptr = True

    _library.ph_frame_evaluate_javascript.argtypes = [c_void_p, c_char_p]
    _library.ph_frame_evaluate_javascript.restype = c_void_p
    _library.ph_frame_evaluate_javascript._char_ptr = True

    _library.ph_frame_get_url.argtypes = [c_void_p]
    _library.ph_frame_get_url.restype = c_void_p
    _library.ph_frame_get_url._char_ptr = True

    _library.ph_frame_set_url.argtypes = [c_void_p, c_char_p]
    _library.ph_frame_set_url.restype = None

    _library.ph_frame_load.argtypes = [c_void_p, c_char_p]
    _library.ph_frame_load.restype = None

    # Image methods
    _library.ph_frame_capture_image.argtypes = [c_void_p, c_char_p, c_int]
    _library.ph_frame_capture_image.restype = c_void_p

    _library.ph_image_get_size.argtypes = [c_void_p]
    _library.ph_image_get_size.restype = c_longlong

    _library.ph_image_get_format.argtypes = [c_void_p]
    _library.ph_image_get_format.restype = c_char_p

    _library.ph_image_free.argtypes = [c_void_p]
    _library.ph_image_free.restype = None

    _library.ph_image_get_bytes.argtypes = [c_void_p, c_void_p, c_longlong]
    _library.ph_image_get_bytes.restype = None

    # Web Element Collection methods
    _library.ph_webcollection_size.argtypes = [c_void_p]
    _library.ph_webcollection_size.restype = c_int

    _library.ph_webcollection_get_webelement.argtypes = [c_void_p, c_int]
    _library.ph_webcollection_get_webelement.restype = c_void_p

    _library.ph_webcollection_free.argtypes = [c_void_p]
    _library.ph_webcollection_free.restype = None

    # Web Element methods
    _library.ph_frame_find_all.argtypes = [c_void_p, c_char_p]
    _library.ph_frame_find_all.restype = c_void_p

    _library.ph_webelement_free.argtypes = [c_void_p]
    _library.ph_webelement_free.restype = None

    _library.ph_webelement_tag_name.argtypes = [c_void_p]
    _library.ph_webelement_tag_name.restype = c_void_p
    _library.ph_webelement_tag_name._char_ptr = True

    _library.ph_webelement_inner_html.argtypes = [c_void_p]
    _library.ph_webelement_inner_html.restype = c_void_p
    _library.ph_webelement_inner_html._char_ptr = True

    _library.ph_webelement_inner_text.argtypes = [c_void_p]
    _library.ph_webelement_inner_text.restype = c_void_p
    _library.ph_webelement_inner_text._char_ptr = True

    _library.ph_webelement_find_all.argtypes = [c_void_p, c_char_p]
    _library.ph_webelement_find_all.restype = c_void_p

    _library.ph_webelement_has_class.argtypes = [c_void_p, c_char_p]
    _library.ph_webelement_has_class.restype = c_int

    _library.ph_webelement_add_class.argtypes = [c_void_p, c_char_p]
    _library.ph_webelement_add_class.restype = None

    _library.ph_webelement_get_classes.argtypes = [c_void_p]
    _library.ph_webelement_get_classes.restype = c_void_p
    _library.ph_webelement_get_classes._char_ptr = True

    _library.ph_webelement_remove_class.argtypes = [c_void_p, c_char_p]
    _library.ph_webelement_remove_class.restype = None

    _library.ph_webelement_get_attr.argtypes = [c_void_p, c_char_p]
    _library.ph_webelement_get_attr.restype = c_void_p
    _library.ph_webelement_get_attr._char_ptr = True

    _library.ph_webelement_set_attr.argtypes = [c_void_p, c_char_p, c_char_p]
    _library.ph_webelement_set_attr.restype = None

    _library.ph_webelement_has_attr.argtypes = [c_void_p, c_char_p]
    _library.ph_webelement_has_attr.restype = c_int

    _library.ph_webelement_remove_attr.argtypes = [c_void_p, c_char_p]
    _library.ph_webelement_remove_attr.restype = None

    _library.ph_webelement_has_attrs.argtypes = [c_void_p]
    _library.ph_webelement_has_attrs.restype = c_int

    _library.ph_webelement_get_attrnames.argtypes = [c_void_p]
    _library.ph_webelement_get_attrnames.restype = c_void_p
    _library.ph_webelement_get_attrnames._char_ptr = True

    _library.ph_webelement_is_null.argtypes = [c_void_p]
    _library.ph_webelement_is_null.restype = c_int

    _library.ph_webelement_append_html.argtypes = [c_void_p, c_char_p]
    _library.ph_webelement_append_html.restype = None

    _library.ph_webelement_append_element.argtypes = [c_void_p, c_void_p]
    _library.ph_webelement_append_element.restype = None

    _library.ph_webelement_append_html_after.argtypes = [c_void_p, c_char_p]
    _library.ph_webelement_append_html_after.restype = None

    _library.ph_webelement_append_element_after.argtypes = [c_void_p, c_void_p]
    _library.ph_webelement_append_element_after.restype = None

    _library.ph_webelement_replace_with_html.argtypes = [c_void_p, c_char_p]
    _library.ph_webelement_replace_with_html.restype = None

    _library.ph_webelement_replace_with_element.argtypes = [c_void_p, c_void_p]
    _library.ph_webelement_replace_with_element.restype = None

    _library.ph_webelement_remove_all_child_elements.argtypes = [c_void_p]
    _library.ph_webelement_remove_all_child_elements.restype = None

    _library.ph_webelement_remove_from_document.argtypes = [c_void_p]
    _library.ph_webelement_remove_from_document.restype = None

    _library.ph_webelement_take_from_document.argtypes = [c_void_p]
    _library.ph_webelement_take_from_document.restype = c_void_p

    _library.ph_webelement_wrap_with_html.argtypes = [c_void_p, c_char_p]
    _library.ph_webelement_wrap_with_html.restype = None

    _library.ph_webelement_wrap_with_element.argtypes = [c_void_p, c_void_p]
    _library.ph_webelement_wrap_with_element.restype = None

    _library.ph_webelement_previous.argtypes = [c_void_p]
    _library.ph_webelement_previous.restype = c_void_p

    _library.ph_webelement_next.argtypes = [c_void_p]
    _library.ph_webelement_next.restype = c_void_p

    _library.ph_webelement_evaluate_javascript.argtypes = [c_void_p, c_char_p]
    _library.ph_webelement_evaluate_javascript.restype = c_void_p
    _library.ph_webelement_evaluate_javascript._char_ptr = True

except (AttributeError, OSError, IOError):
    warnings.warn('libphantompy shared library not found or incompatible')
    _library = object()


def _wrap_char_pointer_function(func):
    def _char_pointer_wrapper(*args, **kwargs):
        ptr = func(*args, **kwargs)
        data = ctypes.cast(ptr, ctypes.c_char_p).value
        _library.ph_free_charptr(ptr)
        return data

    return _char_pointer_wrapper


class ExternLibraryInterface(object):
    def __init__(self, lib):
        self._clib = lib

    def ph_image_get_bytes(self, ptr, size):
        blob = ctypes.create_string_buffer(size)
        self._clib.ph_image_get_bytes(ptr, ctypes.byref(blob), size)
        return blob.raw

    def __getattr__(self, name):
        attr = getattr(self._clib, name)
        if getattr(attr, "_char_ptr", False):
            return _wrap_char_pointer_function(attr)
        return attr

library = ExternLibraryInterface(_library)
