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

    def __del__(self):
        lib.ph_webelement_free(self.ptr)

    @property
    def name(self):
        return self._tag_name

    def has_class(self, classname):
        classname = util.force_bytes(classname)
        result = lib.ph_webelement_has_class(self.ptr, classname)
        return util.int_to_bool(result)

    def has_attr(self, attrname):
        attrname = util.force_bytes(attrname)
        result = lib.ph_webelement_has_attr(self.ptr, attrname)
        return util.int_to_bool(result)

    def has_attrs(self):
        result = lib.ph_webelement_has_attrs(self.ptr)
        return util.int_to_bool(result)

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
