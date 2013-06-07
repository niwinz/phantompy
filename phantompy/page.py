# -*- coding: utf-8 -*-

import json

from .api import library as lib

from . import context
from . import image
from . import webelements
from . import util


class Frame(object):
    def __init__(self, frame_ptr, page):
        self._frame_ptr = frame_ptr
        self._page = page

    def __del__(self):
        lib.ph_frame_free(self._frame_ptr)

    @property
    def ptr(self):
        return self._frame_ptr

    @property
    def url(self):
        return util.force_text(lib.ph_frame_get_url(self.ptr))

    @url.setter
    def url(self, value):
        #lib.ph_frame_load(self.ptr, util.force_bytes(value))
        lib.ph_frame_set_url(self.ptr, util.force_bytes(value))

    @property
    def page(self):
        return self._page

    def to_html(self):
        return lib.ph_frame_to_html(self.ptr)

    def to_image(self, format="PNG", quality=-1):
        _format = util.force_bytes(format)

        # Obtain image object pointer
        image_ptr = lib.ph_frame_capture_image(self.ptr, _format, quality)
        return image.Image(image_ptr, format, quality, self)

    def evaluate(self, js):
        js = util.force_bytes(js)
        result = lib.ph_frame_evaluate_javascript(self.ptr, js)
        return json.loads(util.force_text(result))

    @util.as_list
    def cssselect(self, selector):
        selector = util.force_bytes(selector)
        c_ptr = lib.ph_frame_find_all(self.ptr, selector)
        c_size = lib.ph_webcollection_size(c_ptr)

        for i in range(c_size):
            el_ptr = lib.ph_webcollection_get_webelement(c_ptr, i)
            yield webelements.WebElement(el_ptr, self)

        lib.ph_webcollection_free(c_ptr)


class Page(object):
    _size = None
    _page_ptr = None

    def __init__(self, size=(1280, 768), cookies=[]):
        self._size = size

        self._page_ptr = lib.ph_page_create()
        lib.ph_page_set_viewpoint_size(self.ptr,
                                       self._size[0],
                                       self._size[1])
        if cookies:
            self._context.set_cookies(cookies)

    @property
    def ptr(self):
        return self._page_ptr

    def __del__(self):
        lib.ph_page_free(self.ptr)

    def load(self, url):
        result = lib.ph_page_load(self.ptr, util.force_bytes(url))
        if result != 0:
            raise RuntimeError("Error loading page")

    def frame(self):
        frame_ptr = lib.ph_page_main_frame(self.ptr)
        return Frame(frame_ptr, self)

    def get_requested_urls(self):
        requested_urls = lib.ph_page_get_requested_urls(self.ptr)
        return json.loads(util.force_text(requested_urls))

    def get_response_by_url(self, url):
        """
        Get a background response by url.

        Every page what contains a links to external resources, requires
        a make extra background request for load all page.
        With this method you can access to all response data
        ot their requests.

        :param str url: a url string
        :rtype: dict
        """

        response = lib.ph_page_get_reply_by_url(self.ptr, util.force_bytes(url))
        return json.loads(util.force_text(response))

    @util.as_list
    def get_all_responses(self):
        for url in self.get_requested_urls():
            yield self.get_response_by_url(url)

    def get_cookies(self):
        """
        Get all cookies assiociated with a current
        page url.
        """
        cookies = lib.ph_page_get_cookies(self.ptr)
        return json.loads(cookies.decode("utf-8"))

    def go_back(self):
        lib.ph_page_go_back(self.ptr)

    def go_forward(self):
        lib.ph_page_go_forward(self.ptr)
