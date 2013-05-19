# -*- coding: utf-8 -*-

import json

from .api import library as lib
from .api import ctypes

from . import context
from . import image
from . import webelements


def open(url, size=(1280, 768), ctx=None):
    if ctx is None:
        ctx = context.get_context()

    page = Page(url=url, size=size, ctx=ctx)
    page.load()

    return page.main_frame()


class Frame(object):
    def __init__(self, frame_ptr, page):
        self._frame_ptr = frame_ptr
        self._page = page

    def __del__(self):
        lib.ph_frame_free(self._frame_ptr)

    @property
    def ptr(self):
        assert not self._page.is_closed(), "Page closed"
        return self._frame_ptr

    @property
    def page(self):
        return self._page

    def to_html(self):
        return lib.ph_frame_to_html(self.ptr)

    def to_image(self, format="PNG", quality=-1):
        if hasattr(format, "encode"):
            _format = format.encode("utf-8")
        else:
            _format = format

        # Obtain image object pointer
        image_ptr = lib.ph_frame_capture_image(self.ptr, _format, quality)
        return image.Image(image_ptr, format, quality, self)

    def evaluate(self, js):
        if hasattr(js, "encode"):
            js = js.encode("utf-8")

        result = lib.ph_frame_evaluate_javascript(self.ptr, js)
        return result.decode('utf-8')

    def cssselect(self, selector):
        if hasattr(selector, "encode"):
            selector = selector.encode('utf-8')

        el_ptr = lib.ph_frame_find_first(self.ptr, selector)
        return webelements.WebElement(el_ptr, self)


class Page(object):
    _context = None
    _context_own = False
    _size = None
    _loaded = False
    _closed = False
    _page_ptr = None

    def __init__(self, url, size=(1280, 768), ctx=None):
        if ctx is None:
            self._context = context.Context()
            self._context_own = True
        else:
            self._context = ctx

        self._url = url
        self._size = size

        self._page_ptr = lib.ph_page_create()
        lib.ph_page_set_viewpoint_size(self.ptr,
                                       self._size[0],
                                       self._size[1])

    def close(self):
        assert not self._closed, "Page already closed"
        lib.ph_page_free(self.ptr)

        if self._context_own:
            self._context.close()

        self._closed = True

    def is_closed(self):
        return self._closed

    def load(self):
        assert not self._loaded, "Page already loaded"

        self._loaded = True
        result = lib.ph_page_load(self.ptr, self._url.encode('utf-8'))

        if result != 0:
            raise RuntimeError("Error loading page")

    def frame(self):
        frame_ptr = lib.ph_page_main_frame(self.ptr)
        return Frame(frame_ptr, self)

    def cookies(self):
        assert self._loaded, "Page not loaded"
        cookies_raw_data = lib.ph_page_cookies(self.ptr)
        return json.loads(cookies_raw_data.decode("utf-8"))

    @property
    def ptr(self):
        assert not self._closed, "Page closed"
        return self._page_ptr
