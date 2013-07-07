============
Installation
============

Distribute & Pip
----------------

You can install **phantompy** with `pip` (see :ref:`C/C++ library installation notes <cpp-notes>`):

.. code-block:: console

    pip install phantompy


Get the Code
------------

Also, you can download the latest version from github_ and install
it manually:

.. code-block:: console

    git clone https://github.com/niwibe/phantompy
    cd phantompy
    python setup.py install


.. _github: https://github.com/niwibe/phantompy


Additional notes
----------------

.. _cpp-notes:


C/C++ Library Notes
^^^^^^^^^^^^^^^^^^^

The core part of **phantompy** is a c/c++ library that uses qt5 for access to
WebKit engine (with Qt5WebKit).

Before use of python library/wrapper for libphantompy, you need install system-wide
this c/c++ library.

For compile it, you need:

* Gcc >= 4.8 or clang++ >= 3.2 (simply not tested with previous versions)
* Qt5 (Core, Network, WebKit, Widgets)
* CMake >= 2.8.4

Compile and install instructions:

.. code-block:: console

    cd build
    cmake ..
    make
    sudo make install


NOTES:

* This library has limited tested environtments. If you can compile in other environments
  would be helpful if you notified me of it.
* This library does not works properly on OSX, any help is welcome.


Ubuntu instalation notes
^^^^^^^^^^^^^^^^^^^^^^^^

I have not been able to install all modules needed by phantompy on ubuntu. Ubuntu sucks.
If you get compile, notify me so I can fill this gap with useful information.


Python Compatibility
^^^^^^^^^^^^^^^^^^^^

This python bindings library is build with python3 in mind and has some layer of compatibility
with python2.
