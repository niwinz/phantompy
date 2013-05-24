# -*- coding: utf-8 -*-

from .api import library as lib


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
        return lib.ph_image_get_bytes(self.ptr, self.size)

    def save(self, path):
        with open(path, "wb") as f:
            return f.write(self.to_blob())
