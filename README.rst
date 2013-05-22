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

Currently there is no documentation available. You can look at **tests.py** to
see some examples.

A lot of features are proof of concept and need more work.



Installation
^^^^^^^^^^^^

To compile and install **libphantompy** you need g++ 4.8 (not tested with
previous versions), qt5 and cmake 2.8.8+

.. code-block:: console

    cd build
    cmake ..
    sudo make install

For installing the python module:

.. code-block:: console

    python setup.py install


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