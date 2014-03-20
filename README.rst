=================================
Headless WebKit engine for Python
=================================

Phantompy is a headless scriptable WebKit engine with a clean pythonic api.

**WARNING**: This project is abandoned due big design problems (python always works outside the QT
eventloop, that makes some thins like js events management very ugly and some other things impossible).
I can give the project to any one that want continue the development.

Components
----------

The package has two components:

* C++/C library which exposes a on-demand api to Qt5/QtWebkit (libphantompy)
* Python app that builds on top of **libphantompy** with ctypes

Tested with python: cpython-3.3, cpython-2.7 and pypy-2.0.1


Documentation
-------------

Partial documentation available on: https://phantompy.readthedocs.org/en/latest/

A lot of features are proof of concept and need more work.


Thanks
------

* Benjamin Torsten Jolitz (@benjolitz) for the many ideas submitted.


FAQ
---

**How truly headless is phantompy?**

Thanks to Qt5 and QPA it's truly headless. You can run your apps
without x11 with this environment variable:

.. code-block:: bash

    export QT_QPA_PLATFORM=minimal
