# -*- coding: utf-8 -*-

from .api import library as lib


class Image(object):
    def __init__(self, page, blob, format):
        self._page = page
        self._blob = blob

    @property
    def blob(self):
        return self._blob

    def save(self, path):
        with io.open(path, "wb") as f:
            return f.write(self._blob)
