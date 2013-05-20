# -*- coding: utf-8 -*-

from .api import library as lib
from .api import ctypes


class Image(object):
    def __init__(self, image_ptr, format, quality, frame):
        self._image_ptr = image_ptr
        self._format = format
        self._quality = quality
        self._frame = frame
        self._closed = False

    def __del__(self):
        lib.ph_image_free(self.ptr)

    @property
    def ptr(self):
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
        with open(path, "wb") as f:
            return f.write(self.to_blob())
