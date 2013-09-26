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

    #Set paper size for PDF output
    def set_paper_size(self, paper_size_dict):
        arguments = {
            'width':            { },
            'height' :          { },
            'margin':           { },
            'format':           {'values': ['A0', 'A1', 'A2', 'A3', 'A4', 'A5', 'A6', 'A7', 'A8',
                                             'A9', 'B0', 'B1', 'B2', 'B3', 'B4', 'B5', 'B6', 'B7',
                                             'B8', 'B9', 'B10', 'C5E', 'Comm10E', 'DLE', 'Executive',
                                             'Folio', 'Ledger', 'Legal', 'Letter', 'Tabloid']  },
            'orientation':      { 'values':['landscape', 'potrait'] },
        }

        result = {}
        paper_format = paper_size_dict.get('format')
        paper_orientation = paper_size_dict.get('orientation')

        if 'height' in paper_size_dict and 'width' in paper_size_dict and 'margin' in paper_size_dict:
            result['height'] = paper_size_dict['height']
            result['width'] = paper_size_dict['width']
            result['margin'] = paper_size_dict['margin']

        if paper_format:
            if paper_format.lower() in (value.lower() for value in arguments['format']['values']):
                result['format'] = paper_size_dict['format']
            else:
                raise ValueError('Valid values for the argument "%s" are %s' % ('format', arguments['format']['values']))


        if paper_orientation:
            if paper_orientation.lower() in (value.lower() for value in arguments['orientation']['values']):
                result['orientation'] = paper_size_dict['orientation']
            else:
                raise ValueError('Valid values for the argument "%s" are %s' % ('orientation', arguments['orientation']['values']))

        if not result:
            raise ValueError('Either format or orientation or (height, width and height) are expected')

        lib.ph_frame_set_paper_size(self.ptr, util.force_bytes(json.dumps(paper_size_dict)))

        return None

    #Output to PDF
    def to_pdf(self, fileName):
        lib.ph_frame_render_pdf(self.ptr, fileName)
        return None

    def evaluate(self, js, expect_load=False, timeout=6000):
        js = util.force_bytes(js)
        result = lib.ph_frame_evaluate_javascript(self.ptr, js, expect_load, timeout)
        try:
            return json.loads(util.force_text(result))
        except ValueError:
            return None

    def cssselect_first(self, selector):
        selector = util.force_bytes(selector)

        c_ptr = lib.ph_frame_find_all(self.ptr, selector)
        c_size = lib.ph_webcollection_size(c_ptr)

        if c_size == 0:
            try:
                raise ValueError("Element not found")
            finally:
                lib.ph_webcollection_free(c_ptr)

        try:
            el_ptr = lib.ph_webcollection_get_webelement(c_ptr, 0)
            return webelements.WebElement(el_ptr, self)
        finally:
            lib.ph_webcollection_free(c_ptr)

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
    _context = None
    _size = None
    _page_ptr = None

    def __init__(self, size=(1280, 768), ctx=None, cookies=[]):
        if ctx is None:
            self._context = context.Context()
        else:
            self._context = ctx

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
