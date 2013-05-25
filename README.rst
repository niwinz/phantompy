=================================
Headless WebKit engine for Python
=================================

Phantompy is a headless scriptable WebKit engine with a clean pythonic api.

**Note:** Currently in an early stage of development. Use it for experiments only.

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


FAQ
---

**How truly headless is phantompy?**

Thanks to Qt5 and QPA it's truly headless. You can run your apps
without x11 with this environment variable:

.. code-block:: bash

    export QT_QPA_PLATFORM=minimal


**Can you compile and use phantompy on OSX?**

Yes and no. To build phantompy library on OSX you need to put
``SET(CMAKE_PREFIX_PATH "/usr/local/opt/qt5")`` with valid qt5 installation prefix
on CMakeLists.txt

But the python library does not work properly because it cannot import a library
due to some load imports.

I'm not an OSX expert and improvements are welcome.
