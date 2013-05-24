# -*- coding: utf-8 -*-

from .api import library as lib
from .api import ctypes

from . import page
from . import context
from . import image
from . import webelements


def open(url, size=(1280, 768)):
    ctx = context.context()
    p = page.Page(url=url, size=size, ctx=ctx)
    p.load()

    return p.frame()

