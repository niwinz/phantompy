# -*- coding: utf-8 -*-

import unittest
import io
import time

import phantompy as ph


class WebPageTests(unittest.TestCase):
    def test_load_page(self):
        frame = ph.open("http://127.0.0.1/test.html")
        html_data = frame.to_html()
        self.assertNotEqual(len(html_data), 0)

    def test_evaluate_js(self):
        frame = ph.open("http://127.0.0.1/test.html")
        result = frame.evaluate('document.getElementsByTagName("h1")[0].innerHTML')
        self.assertEqual(result, "Title")

    def test_page_cookies(self):
        frame = ph.open("http://www.facebook.com")
        cookies = frame.page.cookies()
        self.assertIsInstance(cookies, dict)


class WebElementTests(unittest.TestCase):
    def test_get_title_element(self):
        p = ph.open("http://127.0.0.1/test.html")

        element = p.cssselect("title")
        self.assertEqual(element.name, "TITLE")
        self.assertEqual(element.inner_html(), "simple title")

    def test_get_null_element(self):
        p = ph.open("http://127.0.0.1/test.html")

        element = p.cssselect("foo")
        self.assertTrue(element.is_none())

    def test_get_inner_html(self):
        p = ph.open("http://127.0.0.1/test.html")

        element = p.cssselect("#footer")
        html = element.inner_html()
        self.assertEqual(html.strip(), "<span>some footer</span>")

    def test_get_inner_text(self):
        p = ph.open("http://127.0.0.1/test.html")

        element = p.cssselect("#footer")
        text = element.inner_text()
        self.assertEqual(text.strip(), "some footer")


class WebPageImageTests(unittest.TestCase):
    def test_capture_page(self):
        p = ph.open("http://127.0.0.1/test.html")
        img = p.to_image()
        blob = img.to_blob()

        self.assertEqual(len(blob), 10931)


if __name__ == "__main__":
    unittest.main()
