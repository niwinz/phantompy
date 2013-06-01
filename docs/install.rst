============
Installation
============


You can install **phantompy** with `pip`:

.. code-block:: console

    pip install phantompy


Also, you can download the latest version from github_ and install
it manually:

.. code-block:: console

    git clone https://github.com/niwibe/phantompy
    cd phantompy
    python setup.py install


.. _github: https://github.com/niwibe/phantompy


Notes about C/C++ Library
-------------------------

The core part of **phantompy** is a c/c++ library that uses qt5 for access to
WebKit engine (with Qt5WebKit).

On installation time of **phantompy** you need compile this library, is really transparent
but you need have installed some system dependences:

* Gcc >= 4.8 (not tested with lower version)
* Qt5 (Core, Network, WebKit, Widgets)
* CMake >= 2.8.4


Also:

* Clang version found on OSX (3.2~) can compile this library but with clang 3.2 on
  linux, qt5 has one bug and can not compile it with -std=c++11
* This library has limited tested environtments. If you can compile in other environments
  would be helpful if you notified me of it.
* This library does not works properly on OSX, any help is welcome.


Compatibility
-------------

This python bindings library is build with python3 in mind and has some layer of compatibility
with python2.

Currently all tests passes with python-3.3, but with python2.7 or pypy-2.0 works
the majority of the api.
