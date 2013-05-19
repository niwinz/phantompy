# -*- coding: utf-8 -*-

from .api import library as lib
from .api import ctypes


class Image(object):
    def __init__(self, image_ptr, format, quality, page):
        self._image_ptr = image_ptr
        self._format = format
        self._quality = quality
        self._page = page
        self._closed = False

    def close(self):
        assert not self._closed, "Image already closed"
        lib.ph_image_free(self.ptr)
        self._closed = True

    def __enter__(self):
        return self

    def __exit__(self, *args, **kwargs):
        self.close()

    @property
    def ptr(self):
        assert not self._closed, "Image closed"
        assert not self._page.is_closed(), "Page closed"
        return self._image_ptr

    @property
    def size(self):
        return lib.ph_image_get_size(self.ptr)

    def to_blob(self):
        # Get image size
        image_size = self.size

        # Get image binary data
        blob = ctypes.create_string_buffer(image_size)
        lib.ph_image_get_bytes(self.ptr, ctypes.byref(blob), image_size)

        return blob.raw

    def save(self, path):
        with io.open(path, "wb") as f:
            return f.write(self.to_blob())
