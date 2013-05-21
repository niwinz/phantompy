=================================
Headless WebKit engine for Python
=================================

Phantompy is a headless WebKit engine scriptable with a clean pythonic api.

**Note:** Currently in earlier stage of development. Use it for experiment only.

Components
----------

The package has two components:

* C++/C library what exposes a ondemand api to Qt5/QtWebkit (libphantompy)
* Python app build on top of the **libphantompy** with ctypes

Tested with python: cpython-3.3, cpython-2.7 and pypy-2.0.1


Documentation
-------------

Currently there is no documentation available. You can see **tests.py** file for
see some examples.

A lot of features are proof of concept and need more work.



Installation
^^^^^^^^^^^^

For compile and install a **libphantompy** you need g++ 4.8 (not tested with
previous versions), qt5 and cmake 2.8.8+

.. code-block:: console

    cd build
    cmake ..
    sudo make install

For install python module:

.. code-block:: console

    python setup.py install


FAQ
---

**How truly headless is a phantompy?**

Thanks to Qt5 and QPA is truly headless. You can run your apps
without x11 with this environment variable:

.. code-block:: bash

    export QT_QPA_PLATFORM=minimal


**Can compile and use phantompy on OSX?**

Yes and Not. For build phantompy library you need put
``SET(CMAKE_PREFIX_PATH "/usr/local/opt/qt5")`` with valid qt5 instalation prefix
on CMakeLists.txt

But python library does not works properly because can not import a library
due some load imports.

I'm not osx expert and improvements are welcome.
