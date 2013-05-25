# -*- coding: utf-8 -*-

from .api import library as lib
from . import util


class WebElement(object):
    def __init__(self, el_ptr, frame):
        self._el_ptr = el_ptr
        self._frame = frame
        self._closed = False

        # Setup tagname
        tagname = lib.ph_webelement_tag_name(el_ptr)
        self._tag_name = tagname.decode("utf-8")

    def __repr__(self):
        return "<WebElement <{0}> >".format(self.name)

    @property
    def ptr(self):
        return self._el_ptr

    @property
    def frame(self):
        return self._frame

    def __del__(self):
        lib.ph_webelement_free(self.ptr)

    @property
    def name(self):
        return self._tag_name

    def get_classes(self):
        classes = util.force_text(lib.ph_webelement_get_classes(self.ptr))
        return classes.split()

    def has_class(self, classname):
        classname = util.force_bytes(classname)
        result = lib.ph_webelement_has_class(self.ptr, classname)
        return util.int_to_bool(result)

    def remove_class(self, classname):
        if self.has_class(classname):
            lib.ph_webelement_remove_class(self.ptr, util.force_bytes(classname))

    def has_attr(self, attrname):
        attrname = util.force_bytes(attrname)
        result = lib.ph_webelement_has_attr(self.ptr, attrname)
        return util.int_to_bool(result)

    def has_attrs(self):
        result = lib.ph_webelement_has_attrs(self.ptr)
        return util.int_to_bool(result)

    def remove_attr(self, attrname):
        if self.has_attr(attrname):
            lib.ph_webelement_remove_attr(self.ptr, util.force_bytes(attrname))

    def append(self, element):
        if isinstance(element, util.string_type):
            lib.ph_webelement_append_html(self.ptr, util.force_bytes(element))
        elif isinstance(element, WebElement):
            lib.ph_webelement_append_element(self.ptr, element.ptr)
        else:
            raise RuntimeError("Invalid argument")

    def append_after(self, element):
        if isinstance(element, util.string_type):
            lib.ph_webelement_append_html_after(self.ptr, util.force_bytes(element))
        elif isinstance(element, WebElement):
            lib.ph_webelement_append_element_after(self.ptr, element.ptr)
        else:
            raise RuntimeError("Invalid argument")

    def replace(self, element):
        if isinstance(element, util.string_type):
            lib.ph_webelement_replace_with_html(self.ptr, util.force_bytes(element))
        elif isinstance(element, WebElement):
            lib.ph_webelement_replace_with_element(self.ptr, element.ptr)
        else:
            raise RuntimeError("Invalid argument")

    def replace(self, element):
        if isinstance(element, util.string_type):
            lib.ph_webelement_replace_with_html(self.ptr, util.force_bytes(element))
        elif isinstance(element, WebElement):
            lib.ph_webelement_replace_with_element(self.ptr, element.ptr)
        else:
            raise RuntimeError("Invalid argument")

    def remove_childs(self):
        lib.ph_webelement_remove_all_child_elements(self.ptr)

    def remove(self):
        lib.ph_webelement_remove_from_document(self.ptr)

    def wrap(self, element):
        if isinstance(element, util.string_type):
            lib.ph_webelement_wrap_with_html(self.ptr, util.force_bytes(element))
        elif isinstance(element, WebElement):
            lib.ph_webelement_wrap_with_element(self.ptr, element.ptr)
        else:
            raise RuntimeError("Invalid argument")

    def next(self):
        ptr = lib.ph_webelement_next(self.ptr)
        return WebElement(ptr, self.frame)

    def prev(self):
        ptr = lib.ph_webelement_previous(self.ptr)
        return WebElement(ptr, self.frame)

    @util.as_dict
    def get_attrs(self):
        attr_names = lib.ph_webelement_get_attrnames(self.ptr)
        for name in util.force_text(attr_names).split():
            value = lib.ph_webelement_get_attr(self.ptr, util.force_bytes(name))
            yield name, util.force_text(value)

    def inner_html(self):
        result = lib.ph_webelement_inner_html(self.ptr)
        return util.force_text(result)

    def inner_text(self):
        result = lib.ph_webelement_inner_text(self.ptr)
        return util.force_text(result)

    def is_none(self):
        result = lib.ph_webelement_is_null(self.ptr)
        return util.int_to_bool(result)

    @util.as_list
    def cssselect(self, selector):
        selector = util.force_bytes(selector)

        c_ptr = lib.ph_webelement_find_all(self.ptr, selector)
        c_size = lib.ph_webcollection_size(c_ptr)

        for i in range(c_size):
            el_ptr = lib.ph_webcollection_get_webelement(c_ptr, i)
            yield WebElement(el_ptr, self)

        lib.ph_webcollection_free(c_ptr)
