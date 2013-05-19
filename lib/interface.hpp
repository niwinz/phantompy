#include <stdint.h>
#include "page.hpp"

extern "C" {
    // Initialize methods
    void* ph_engine_init();
    void ph_engine_free(void* engine);

    // Page Methods
    void* ph_page_create();
    void ph_page_set_viewpoint_size(void *page, int x, int y);
    void ph_page_free(void *page);

    int32_t ph_page_load(void *page, char *url);
    int32_t ph_page_is_loaded(void *page);

    char* ph_page_to_html(void *page);

    int64_t ph_page_capture_image(void *page, char *format, int quality);
    void ph_page_captured_image_bytes(void *page, void* buffer, int64_t size);

    char* ph_page_evaluate_javascript(void *page, char* js);
}
