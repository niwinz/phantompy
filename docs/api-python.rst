==========
Python Api
==========

This is the technical documentation of the python bindins **libphantompy**'s
API.

Context & Config
----------------

:py:class:`~phantompy.context.Context` class represents a context singleton
pointer that contains an instance of a QT application, an interface for some
WebKit engine configuration options and some actions (e.g. clear cache memory).

.. automodule:: phantompy.context
    :members:
    :undoc-members:


Web Element
-----------

Live DOM manipulation and transversing api.

.. automodule:: phantompy.webelements
    :members:
    :undoc-members:
