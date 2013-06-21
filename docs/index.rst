.. phantompy documentation master file, created by
   sphinx-quickstart on Sat May 25 00:22:39 2013.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

phantompy
=========

Release v\ |version|.

phantompy is a :ref:`BSD Licensed`, headless WebKit engine with a powerful pythonic api.

Introduction
------------

This package has two main components:

* C/C++ Library which exposes some portions of the WebKit API from Qt5 (libphantompy).
* Python bindings for **libphantompy**


Features
--------

.. note::

    One or more of the listed features are not implemented. And others are only a proof
    of concept and have a limited API.

- Live DOM access in a pythonic way. (Proof of concept API implemented)
- Totally configurable (currently only limited config options are exposed to Python)
- Access to a frames tree created by a page.
- Access to background requests of one page.

User guide
----------

.. toctree::
    :maxdepth: 2

    install.rst


Developers Api
--------------

.. toctree::
   :maxdepth: 1

   api-python.rst
   api-ctypes.rst
