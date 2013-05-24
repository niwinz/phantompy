#include <stdint.h>
#include <cstring>


extern "C" {
    // Initialize methods
    void* ph_context_init();
    void ph_context_free(void* context);

    void ph_context_clear_memory_cache();
    void ph_context_set_object_cache_capacity(int i, int x, int z);
    void ph_context_set_max_pages_in_cache(int num);

    void ph_context_set_boolean_config(int key, int value);

    // Page Methods
    void* ph_page_create();
    void ph_page_set_viewpoint_size(void *page, int x, int y);
    void ph_page_free(void *page);

    int32_t ph_page_load(void *page, char *url);
    int32_t ph_page_is_loaded(void *page);

    char* ph_page_cookies(void *page);
    char* ph_page_requested_urls(void *page);

    // Frame
    void* ph_page_main_frame(void *page);
    void ph_frame_free(void *frame);

    char* ph_frame_to_html(void *frame);
    char* ph_frame_evaluate_javascript(void *frame, char* js);

    // Image Methods
    void* ph_frame_capture_image(void *frame, const char *format, int quality);
    void ph_image_free(void *image);
    int64_t ph_image_get_size(void* image);
    const char* ph_image_get_format(void* image);
    void ph_image_get_bytes(void *image, void *buffer, int64_t size);

    // Web element methods
    void* ph_frame_find_first(void *frame, const char *selector);
    void ph_webelement_free(void *el);

    char* ph_webelement_tag_name(void *el);
    char* ph_webelement_inner_html(void *el);
    char* ph_webelement_inner_text(void *el);

    int32_t ph_webelement_has_class(void *el, const char *classname);
    int32_t ph_webelement_has_attr(void *el, const char *attrname);
    int32_t ph_webelement_has_attrs(void *el);
    int32_t ph_webelement_is_null(void *el);
}
