=====
C Api
=====

This is technical documentation of the C api, compatible with ctypes. This api is is an intermediate
layer between the c++ library and python. The python bindings uses this API directly via ctypes.

Context
-------

Context is a singleton object that mantains in memory the Qt5 application instance and exposes
some QtWebKit configurations.

The current api is incomplete and in neear future will be exposed a lot of configuration methods
for WebKit engine.

.. c:function:: void* ph_context_init()

    :rtype: pointer to a Context instance.

    This method returns a new context instance. Context is a singleton, and if
    you call repeatedly this method, it always returns a pointer to same object.


.. c:function:: void ph_context_free()

    Destroy a current instance of Context. If you call this method repeatedly, the
    behavior is unexpected.


.. c:function:: void ph_context_clear_memory_cache()

    Clears a memory used by webkit for current thread.

.. c:function:: void ph_context_set_object_cache_capacity(int cacheMinDeadCapacity, int cacheMaxDead, int totalCapacity)

    Specifies the capacities for the memory cache for dead objects such as stylesheets or scripts.

    :param int cacheMinDeadCapacity: specifies the minimum number of bytes that dead objects should consume when the cache is under pressure.
    :param int cacheMaxDead: is the maximum number of bytes that dead objects should consume when the cache is not under pressure.
    :param int totalCapacity: specifies the maximum number of bytes that the cache should consume overall.


.. c:function:: void ph_context_set_max_pages_in_cache(int num)

    Sets the maximum number of pages to hold in the memory page cache to pages.

    :param int num: number of pages to hold in the memory.


Web Page
--------

This api exposes a **web page** and their frames functionality.

.. c:function:: void* ph_page_create()

    Creates a new instance of Page object and returns its pointer.

    :rtype: pointer to a Page object instance.


.. c:function:: void ph_page_free(void *page)

    Destroys a page instance and free memory used by it.

    :param void* page: Page instance pointer returned by :c:func:`ph_page_create`
