=================================
Headless WebKit engine for Python
=================================

Phantompy is a headless WebKit engine scriptable with a clean pythonic api.

Note: Currently in earlier state of development. Use it for experiment only.

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
