# -*- coding: utf-8 -*-

import json

from .api import library as lib
from . import util


class WebElement(object):
    """
    Class that represents a live dom element on
    webkit engine.
    """

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
        """
        Returns a pointer to internal C++ instance object.
        """
        return self._el_ptr

    @property
    def frame(self):
        """
        Returns a frame instance of this element.
        """
        return self._frame

    def __del__(self):
        lib.ph_webelement_free(self.ptr)

    @property
    def name(self):
        """
        Returns a tagname.
        """
        return self._tag_name

    def get_classes(self):
        """
        Returs a list of classes that hace current
        dom element.

        Example:

        .. code-block:: python

            >>> element = p.cssselect("section")[0]
            >>> element.get_classes()
            ["main", "main-section"]
        """
        classes = util.force_text(lib.ph_webelement_get_classes(self.ptr))
        return classes.split()

    def has_class(self, classname):
        """
        Method that checks the existense of some class
        in a current dom element.

        :param str classname: class name
        :rtype: bool

        Example:

        .. code-block:: python

            >>> element = p.cssselect("section")[0].has_class("foo")
            False

        """

        classname = util.force_bytes(classname)
        result = lib.ph_webelement_has_class(self.ptr, classname)
        return util.int_to_bool(result)

    def remove_class(self, classname):
        """
        Method that removes a class from a current
        dom node. If a class does not exists, this method
        does nothink.

        :param str classname: class name
        :rtype: None
        """

        if self.has_class(classname):
            lib.ph_webelement_remove_class(self.ptr, util.force_bytes(classname))

    def has_attr(self, attrname):
        """
        Method that checks the existence of one concrete
        attribute by name.

        :param str attribute: attribute name
        :rtype: bool
        """

        attrname = util.force_bytes(attrname)
        result = lib.ph_webelement_has_attr(self.ptr, attrname)
        return util.int_to_bool(result)

    def has_attrs(self):
        """
        Method that checkos of existence of any attrs. Returns a
        True value if a current dom element has any attribute.

        :rtype: bool
        """

        result = lib.ph_webelement_has_attrs(self.ptr)
        return util.int_to_bool(result)

    def remove_attr(self, attrname):
        """
        Remove attribute by name.

        :param str attrname: attribute name.
        :rtype: None
        """

        if self.has_attr(attrname):
            lib.ph_webelement_remove_attr(self.ptr, util.force_bytes(attrname))

    def append(self, element):
        """
        Append element or raw html to the current dom element.

        :param element: Unicode string with html or WebElement instance.
        :rtype: None

        Example:

        .. code-block:: python

            >>> element = p.cssselect("body > section")[0]
            >>> element.append("<span>{0}</span>".format("FOO"))

        """

        if isinstance(element, util.string_type):
            lib.ph_webelement_append_html(self.ptr, util.force_bytes(element))
        elif isinstance(element, WebElement):
            lib.ph_webelement_append_element(self.ptr, element.ptr)
        else:
            raise RuntimeError("Invalid argument")

    def append_after(self, element):
        """
        Same as :py:meth:`~.append` but appends outside the current
        dom element.
        """

        if isinstance(element, util.string_type):
            lib.ph_webelement_append_html_after(self.ptr, util.force_bytes(element))
        elif isinstance(element, WebElement):
            lib.ph_webelement_append_element_after(self.ptr, element.ptr)
        else:
            raise RuntimeError("Invalid argument")

    def replace(self, element):
        """
        Replace the current element with other.

        :param element: Unicode string with html or :py:class:`~WebElement` instance.
        :rtype: None

        """

        if isinstance(element, util.string_type):
            lib.ph_webelement_replace_with_html(self.ptr, util.force_bytes(element))
        elif isinstance(element, WebElement):
            lib.ph_webelement_replace_with_element(self.ptr, element.ptr)
        else:
            raise RuntimeError("Invalid argument")

    def remove_childs(self):
        """
        Remove all childs of the current dom.
        """

        lib.ph_webelement_remove_all_child_elements(self.ptr)

    def remove(self):
        """
        Remove the current element from the living dom and make
        this element as empty element.
        """

        lib.ph_webelement_remove_from_document(self.ptr)

    def wrap(self, element):
        """
        Wraps the current element with other element.

        :param element: Unicode string with html or :py:class:`~WebElement` instance.
        :rtype: None

        Example:

        .. code-block:: python

            >>> element = p.cssselect("a")[0]
            >>> element.wrap("<div/>")

        """

        if isinstance(element, util.string_type):
            lib.ph_webelement_wrap_with_html(self.ptr, util.force_bytes(element))
        elif isinstance(element, WebElement):
            lib.ph_webelement_wrap_with_element(self.ptr, element.ptr)
        else:
            raise RuntimeError("Invalid argument")

    def next(self):
        """
        Get a next element in the same level of dom.

        :rtype: :py:class:`~WebElement`
        """

        ptr = lib.ph_webelement_next(self.ptr)
        return WebElement(ptr, self.frame)

    def prev(self):
        """
        Get a previous element in the same level of dom.

        :rtype: :py:class:`~WebElement`
        """

        ptr = lib.ph_webelement_previous(self.ptr)
        return WebElement(ptr, self.frame)

    @util.as_dict
    def get_attrs(self):
        """
        Get all attributes as python dict.
        :rtype: dict
        """

        attr_names = lib.ph_webelement_get_attrnames(self.ptr)
        for name in util.force_text(attr_names).split():
            value = lib.ph_webelement_get_attr(self.ptr, util.force_bytes(name))
            yield name, util.force_text(value)

    def inner_html(self):
        """
        Get inner dom structure as html.

        :rtype: str
        """

        result = lib.ph_webelement_inner_html(self.ptr)
        return util.force_text(result)

    def inner_text(self):
        """
        Get inner dom structure as text, stripping all
        html tags.

        :rtype: str
        """

        result = lib.ph_webelement_inner_text(self.ptr)
        return util.force_text(result)

    def is_none(self):
        """
        Checks if a current dom element is empty or not.

        :rtype: bool
        """

        result = lib.ph_webelement_is_null(self.ptr)
        return util.int_to_bool(result)

    @util.as_list
    def cssselect(self, selector):
        """
        Find all descendent elements by css selector
        like jQuery.

        :param str selector: jQuery like selector
        :rtype: list
        """

        selector = util.force_bytes(selector)

        c_ptr = lib.ph_webelement_find_all(self.ptr, selector)
        c_size = lib.ph_webcollection_size(c_ptr)

        for i in range(c_size):
            el_ptr = lib.ph_webcollection_get_webelement(c_ptr, i)
            yield WebElement(el_ptr, self)

        lib.ph_webcollection_free(c_ptr)

    def evaluate(self, js):
        js = util.force_bytes(js)
        result = lib.ph_webelement_evaluate_javascript(self.ptr, js)
        return json.loads(util.force_text(result))
