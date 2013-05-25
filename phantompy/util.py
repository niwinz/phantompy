# -*- coding: utf-8 -*-

import functools
import sys


if sys.version_info[0] == 3:
    string_type = str
    bytes_type = bytes
else:
    string_type = unicode
    bytes_type = str


def as_list(function):
    """
    Convert to list a generator function.
    """
    @functools.wraps(function)
    def _decorator(*args, **kwargs):
        return list(function(*args, **kwargs))
    return _decorator

def as_dict(function):
    """
    Convert to list a generator function.
    """
    @functools.wraps(function)
    def _decorator(*args, **kwargs):
        return dict(list(function(*args, **kwargs)))
    return _decorator

def force_bytes(data, encoding="utf-8"):
    if isinstance(data, string_type):
        data = data.encode(encoding)
    return data

def force_text(data, encoding="utf-8"):
    if isinstance(data, bytes_type):
        data = data.decode(encoding)
    return data

def int_to_bool(data):
    if data == 0:
        return True
    return False
