# -*- coding: utf-8 -*-

from .api import library as lib
from .api import ctypes

from . import page
from . import context
from . import image
from . import webelements


def open(url, size=(1280, 768), cookies=[]):
    ctx = context.context()
    p = page.Page(size=size, cookies=cookies, ctx=ctx)
    p.load(url)
    return p.frame()

