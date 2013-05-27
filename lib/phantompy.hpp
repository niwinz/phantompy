#include <stdint.h>
#include <cstring>

extern "C" {
    // Initialize methods
    void* ph_context_init();
    void ph_context_free(void* context);
    void ph_free_charptr(char *ptr);

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

    //char* ph_page_cookies(void *page);
    char* ph_page_get_requested_urls(void *page);
    char* ph_page_get_reply_by_url(void *page, const char *url);

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
    void* ph_frame_find_first(void *frame, const char *selector); // TODO: deprectated
    void* ph_frame_find_all(void *frame, const char *selector);
    void* ph_webcollection_get_webelement(void *collection,  int32_t index);
    void* ph_webelement_find_all(void *element, const char *selector);
    void* ph_webelement_take_from_document(void *element);
    void* ph_webelement_previous(void *element);
    void* ph_webelement_next(void *element);

    void ph_webcollection_free(void *collection);
    void ph_webelement_free(void *element);

    char* ph_webelement_tag_name(void *element);
    char* ph_webelement_inner_html(void *element);
    char* ph_webelement_inner_text(void *element);
    char* ph_webelement_get_classes(void *element);
    char* ph_webelement_get_attnames(void *element);
    char* ph_webelement_get_attr(void *element, const char *attrname);

    int32_t ph_webcollection_size(void *collection);
    int32_t ph_webelement_has_class(void *element, const char *classname);
    int32_t ph_webelement_has_attr(void *element, const char *attrname);
    int32_t ph_webelement_has_attrs(void *element);
    int32_t ph_webelement_is_null(void *element);

    void ph_webelement_remove_attr(void *element, const char *attrname);
    void ph_webelement_add_class(void *element, const char *classname);
    void ph_webelement_set_attr(void *element, const char *attrname, const char *value);
    void ph_webelement_append_html(void *element, const char *htmldata);
    void ph_webelement_append_element(void *element, void *elementement);
    void ph_webelement_append_html_after(void *element, const char *htmldata);
    void ph_webelement_append_element_after(void *element, void *elementement);
    void ph_webelement_replace_with_html(void *element, const char *htmldata);
    void ph_webelement_replace_with_element(void *element, void *elementement);
    void ph_webelement_remove_all_child_elements(void *element);
    void ph_webelement_remove_from_document(void *element);
    void ph_webelement_wrap_with_html(void *element, const char *htmldata);
    void ph_webelement_wrap_with_element(void *element, void *elementement);
}
