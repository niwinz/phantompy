# -*- coding: utf-8 -*-

from __future__ import unicode_literals

import unittest
import time
from os.path import join, dirname, abspath

import phantompy as ph

CURRENT_DIR = dirname(abspath(__file__))

TEST_FILE = join(CURRENT_DIR, "misc", "test.html")
TEST_FILE_WITH_FRAMES = join(CURRENT_DIR, "misc", "test_with_frames.html")

def setUpModule():
    ctx = ph.context.context()
    ctx.conf.set_max_pages_in_cache(0)
    ctx.conf.set_object_cache_capacity(0, 0, 0)
    ctx.clear_memory_caches()

def tearDownModule():
    ph.context.destroy_context()

class TestCase(unittest.TestCase):
    pass

class WebPageTests(TestCase):
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
        ctx = ph.context.context()

        cookies = ctx.get_all_cookies()
        self.assertNotEqual(len(cookies), 0)
        self.assertIn("value", cookies[0])
        self.assertIn("name", cookies[0])
        self.assertIn("domain", cookies[0])
        self.assertIn("expires", cookies[0])

    def test_page_all_requests(self):
        frame = ph.open(TEST_FILE)
        self.assertIn('http://code.jquery.com/jquery-1.9.1.min.js', frame.page.get_requested_urls())
        self.assertEqual(len(frame.page.get_requested_urls()), 2)

    def test_retrieve_page_background_responses(self):
        frame = ph.open(TEST_FILE)
        response = frame.page.get_response_by_url('http://code.jquery.com/jquery-1.9.1.min.js')

        self.assertNotEqual(response["size"], 0)
        self.assertEqual(response["status"], 200)
        self.assertNotEqual(len(response["headers"]), 0)


    def test_conf_access(self):
        ctx = ph.context.context()
        ctx.conf.load_images = False
        ctx.conf.javascript = False
        ctx.conf.offline_storage_quota = 2000

        self.assertFalse(ctx.conf.load_images)
        self.assertFalse(ctx.conf.javascript)
        self.assertEqual(ctx.conf.offline_storage_quota, 2000)

        ctx.conf.load_images = True
        ctx.conf.javascript = True
        ctx.conf.offline_storage_quota = 0

        self.assertTrue(ctx.conf.load_images)
        self.assertTrue(ctx.conf.javascript)
        self.assertEqual(ctx.conf.offline_storage_quota, 0)


class WebElementTests(TestCase):
    def test_get_title_element(self):
        p = ph.open(TEST_FILE)

        elements = p.cssselect("title")
        self.assertEqual(len(elements), 1)
        self.assertEqual(elements[0].name, "TITLE")
        self.assertEqual(elements[0].inner_html(), "simple title")

    def test_get_null_element(self):
        p = ph.open(TEST_FILE)

        elements = p.cssselect("foo")
        self.assertEqual(len(elements), 0)

    def test_get_inner_html(self):
        p = ph.open(TEST_FILE)

        elements = p.cssselect("#footer")
        self.assertEqual(len(elements), 1)

        html = elements[0].inner_html()
        self.assertEqual(html.strip(), "<span>some footer</span>")

    def test_get_inner_text(self):
        p = ph.open(TEST_FILE)

        elements = p.cssselect("#footer")
        self.assertEqual(len(elements), 1)

        text = elements[0].inner_text()
        self.assertEqual(text.strip(), "some footer")

    def test_inner_cssselect(self):
        p = ph.open(TEST_FILE)
        element = p.cssselect("#footer")[0]

        elements = element.cssselect("span")
        self.assertEqual(len(elements), 1)

    def test_has_attrs(self):
        p = ph.open(TEST_FILE)
        element = p.cssselect("#footer span")[0]
        self.assertFalse(element.has_attrs())

        element = p.cssselect("#footer")[0]
        self.assertTrue(element.has_attrs())
        self.assertTrue(element.has_attr("id"))
        self.assertFalse(element.has_attr("class"))

    def test_has_class(self):
        p = ph.open(TEST_FILE)

        elements = p.cssselect(".section")
        self.assertEqual(len(elements), 2)
        self.assertTrue(elements[0].has_class("barsection"))
        self.assertTrue(elements[1].has_class("foosection"))
        self.assertFalse(elements[1].has_class("barsection"))

    def test_remove_class(self):
        p = ph.open(TEST_FILE)

        elements = p.cssselect(".barsection")
        self.assertEqual(len(elements), 1)

        elements[0].remove_class("barsection")

        elements = p.cssselect(".barsection")
        self.assertEqual(len(elements), 0)

    def test_append_01(self):
        p = ph.open(TEST_FILE)

        element = p.cssselect("#footer")[0]
        self.assertEqual(len(element.cssselect("span")), 1)

        element.append("<span>Fooo</span>")
        self.assertEqual(len(element.cssselect("span")), 2)

    def test_append_02(self):
        p = ph.open(TEST_FILE)

        element = p.cssselect("#footer")[0]
        self.assertEqual(len(element.cssselect("div")), 0)

        tmpelement = p.cssselect(".barsection")[0]
        element.append(tmpelement)

        self.assertEqual(len(element.cssselect("div")), 1)
        self.assertEqual(len(p.cssselect("div")), 4)

    def test_append_after(self):
        p = ph.open(TEST_FILE)
        element = p.cssselect("#footer")[0]

        self.assertEqual(len(element.cssselect("span")), 1)
        self.assertEqual(len(p.cssselect("span")), 1)

        element.append_after("<span>Fooo</span>")
        self.assertEqual(len(element.cssselect("span")), 1)
        self.assertEqual(len(p.cssselect("span")), 2)

    def test_replace_01(self):
        p = ph.open(TEST_FILE)
        element = p.cssselect("#footer")[0]
        element.replace("<section>kk</section>")
        self.assertEqual(len(p.cssselect("#footer")), 0)

    def test_replace_02(self):
        p = ph.open(TEST_FILE)
        element = p.cssselect("#footer")[0]
        element.replace(p.cssselect(".barsection")[0])
        self.assertEqual(len(p.cssselect("#footer")), 0)

    def test_remove_all_childs(self):
        p = ph.open(TEST_FILE)
        element = p.cssselect("#footer")[0]

        self.assertEqual(len(element.cssselect("*")), 1)
        element.remove_childs()
        self.assertEqual(len(element.cssselect("*")), 0)

    def test_remove_from_document(self):
        p = ph.open(TEST_FILE)
        element = p.cssselect("#footer")[0]
        element.remove()

        self.assertEqual(len(p.cssselect("#footer")), 0)
        self.assertTrue(element.is_none())

    def test_wrap(self):
        p = ph.open(TEST_FILE)

        self.assertEqual(len(p.cssselect("section > #footer")), 0)
        element = p.cssselect("#footer")[0]
        element.wrap("<section />")
        self.assertEqual(len(p.cssselect("section > #footer")), 1)

    def test_next(self):
        p = ph.open(TEST_FILE)

        element = p.cssselect(".barsection")[0]
        next_element = element.next()
        self.assertTrue(next_element.has_class("foosection"))

        element = p.cssselect("#div-with-attrs")[0].next()
        self.assertTrue(element.is_none())

    def test_prev(self):
        p = ph.open(TEST_FILE)

        element = p.cssselect(".foosection")[0]
        prev_element = element.prev()
        self.assertTrue(prev_element.has_class("barsection"))

        element = p.cssselect("h1")[0].prev()
        self.assertTrue(element.is_none())

    def test_get_attrs(self):
        p = ph.open(TEST_FILE)
        element = p.cssselect("#div-with-attrs")[0]
        attrs = element.get_attrs()
        self.assertIn("data-id", attrs)
        self.assertEqual(attrs, {'data-id': '1', 'data-url': '/foo', 'id': 'div-with-attrs'})

    def test_get_classes(self):
        p = ph.open(TEST_FILE)
        elements = p.cssselect(".section")

        classes = elements[0].get_classes()

        self.assertEqual(len(classes), 2)
        self.assertEqual(classes, ['section', 'barsection'])

    def test_remove_attr(self):
        p = ph.open(TEST_FILE)
        element = p.cssselect("#div-with-attrs")[0]

        attrs = element.get_attrs()
        self.assertIn("data-id", attrs)

        element.remove_attr("data-id")
        attrs = element.get_attrs()
        self.assertNotIn("data-id", attrs)
        self.assertFalse(element.has_attr("data-id"))


class WebPageImageTests(TestCase):
    def test_capture_page(self):
        p = ph.open(TEST_FILE)
        img = p.to_image()
        blob = img.to_blob()

        self.assertEqual(len(blob), 10931)


if __name__ == "__main__":
    unittest.main()
