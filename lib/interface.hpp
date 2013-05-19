#include "page.hpp"

extern "C" {
    // Initialize methods
    void* ph_engine_init();
    void ph_engine_free(void* engine);

    // Page Methods
    void* ph_page_create();
    void ph_page_set_viewpoint_size(void *page, int x, int y);
    void ph_page_free(void *page);
    int ph_page_load(void *page, char *url);
    int ph_page_is_loaded(void *page);

    char* ph_page_to_html(void *page);
    char* ph_page_to_image_bytes(void *page, char *format, int quality);
    char* ph_page_evaluate_javascript(void *page, char* js);
}
