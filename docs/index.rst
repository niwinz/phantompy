.. phantompy documentation master file, created by
   sphinx-quickstart on Sat May 25 00:22:39 2013.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

phantompy
=========

Release v\ |version|.

phantompy is a :ref:`BSD Licensed`, headless WebKit engine with powerful pythonic api.

Introduction
------------

This package has three main components:

* C/C++ Library that exposes some portion of WebKit api from Qt5 (libphantompy).
* Python bindings for **libphantompy**


Features
--------

.. note::

    One or more of listed features are not implemented. And other are only a proof
    of concept and has limited api.

- Live dom access in pythonic way. (Proof of concept api implemented)
- Totally configurable (currently only limited config options are exposed to python)
- Access to a frames tree created by a page.
- Access to a background requests of one page.

User guide
----------

TODO


Developers Api
--------------

.. toctree::
   :maxdepth: 1

   ctypes_api.rst
   python_api.rst
