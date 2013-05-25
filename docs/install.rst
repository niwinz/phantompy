============
Installation
============

This part of the documentation covers the installation of **libphantompy** library
and python bindings for it.

C/C++ library
-------------

**libphantompy** is build with c++, using Qt5 as main library and uses QtWebKit as
library for access to WebKit engine.

For compile this library you need install some build dependences:

* Gcc >= 4.8 (not tested with lower version)
* Qt5 (Core, Network, WebKit, Widgets)
* CMake >= 2.8.4

These are the commands to compile **libphantompy**:

.. code-block:: console

   cd phantompy/build
   cmake ..
   make
   sudo make install


This installs **libphantompy** on ``/usr/lib/``.


Additional notes
^^^^^^^^^^^^^^^^

* Clang version found on OSX (3.2~) can compile this library but with clang 3.2 on
  linux, qt5 has one bug and can not compile it with -std=c++11
* This library has limited tested environtments. If you can compile in other environments
  would be helpful if you notified me of it.
* This library does not works properly on OSX, any help is welcome.


Python Bindings
---------------

At the moment, python bindins are not available on python package index, because of
a state of development(alpha). in the near future when the api stabilizes, I'll upload one version.

Now, you can install it, downloading it from github and run setup.py script:

.. code-block:: console

    git clone https://github.com/niwibe/phantompy.git
    cd phantompy
    python setup.py install


Compatibility
^^^^^^^^^^^^^

This python bindings library is build with python3 in mind and has some layer of compatibility
with python2.

Currently all tests passes with python-3.3, but with python2.7 or pypy-2.0 works
the majority of the api.
