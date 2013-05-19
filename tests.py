# -*- coding: utf-8 -*-

import unittest
import io

from phantompy import page

class WebPageTests(unittest.TestCase):
    def test_load_page(self):
        p = page.open("http://www.niwi.be")
        html_data = p.to_html()
        self.assertNotEqual(len(html_data), 0)

    def test_evaluate_js(self):
        p = page.open("http://www.niwi.be")
        result = p.evaluate('document.getElementsByTagName("h1")[0].innerHTML')
        self.assertEqual(result, "Articles:")


class WebPageImageTests(unittest.TestCase):
    def test_capture_page(self):
        p = page.open("http://www.niwi.be")
        img = p.to_image()
        self.assertNotEqual(len(img.blob), 0)

        print("KKKKPYTHON", len(img.blob))

        with io.open("/tmp/image.png", "wb") as f:
            f.write(img.blob)


if __name__ == "__main__":
    unittest.main()
