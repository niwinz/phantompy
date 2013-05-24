# -*- coding: utf-8 -*-

import unittest
import time
from os.path import join, dirname, abspath

import phantompy as ph

CURRENT_DIR = dirname(abspath(__file__))

TEST_FILE = join(CURRENT_DIR, "misc", "test.html")
TEST_FILE_WITH_FRAMES = join(CURRENT_DIR, "misc", "test_with_frames.html")


def setUpModule():
    ctx = ph.context.context()
    ctx.set_max_pages_in_cache(0)
    ctx.set_object_cache_capacity(0, 0, 0)
    ctx.clear_memory_caches()

def tearDownModule():
    ph.context.destroy_context()


class WebPageTests(unittest.TestCase):
    def test_load_page(self):
        #import pdb; pdb.set_trace()
        frame = ph.open(TEST_FILE)
        html_data = frame.to_html()
        self.assertNotEqual(len(html_data), 0)

    def test_evaluate_js(self):
        frame = ph.open(TEST_FILE)
        result = frame.evaluate('document.getElementsByTagName("h1")[0].innerHTML')
        self.assertEqual(result, "Title")

    def test_page_cookies(self):
        frame = ph.open("http://www.facebook.com")
        cookies = frame.page.cookies()
        self.assertIsInstance(cookies, dict)

    def test_page_all_requests(self):
        frame = ph.open(TEST_FILE)
        self.assertEqual(frame.page.requested_urls(),
            ['http://code.jquery.com/jquery-1.9.1.min.js'])
        self.assertEqual(len(frame.page.requested_urls()), 1)


class WebElementTests(unittest.TestCase):
    def test_get_title_element(self):
        p = ph.open(TEST_FILE)

        element = p.cssselect("title")
        self.assertEqual(element.name, "TITLE")
        self.assertEqual(element.inner_html(), "simple title")

    def test_get_null_element(self):
        p = ph.open(TEST_FILE)

        element = p.cssselect("foo")
        self.assertTrue(element.is_none())

    def test_get_inner_html(self):
        p = ph.open(TEST_FILE)

        element = p.cssselect("#footer")
        html = element.inner_html()
        self.assertEqual(html.strip(), "<span>some footer</span>")

    def test_get_inner_text(self):
        p = ph.open(TEST_FILE)

        element = p.cssselect("#footer")
        text = element.inner_text()
        self.assertEqual(text.strip(), "some footer")


class WebPageImageTests(unittest.TestCase):
    def test_capture_page(self):
        p = ph.open(TEST_FILE)
        img = p.to_image()
        blob = img.to_blob()

        self.assertEqual(len(blob), 10931)


if __name__ == "__main__":
    unittest.main()
