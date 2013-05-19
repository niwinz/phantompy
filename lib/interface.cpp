#include "interface.hpp"
#include "context.hpp"
#include <cstring>

extern "C" {

void* ph_engine_init() {
    return new Context();
}

void ph_engine_free(void *ctx) {
    Context *context = (Context*)ctx;
    delete context;
}

void* ph_page_create() {
    Page *p = new Page();
    return p;
}

void ph_page_free(void *page) {
    Page *p = (Page*)page;
    delete p;
}

void ph_page_set_viewpoint_size(void *page, int x, int y) {
    Page *p = (Page*)page;
    p->setViewSize(x, y);
}

int ph_page_load(void *page, char *url) {
    Page *p = (Page*)page;
    p->load(QString::fromUtf8(url));

    bool ok = p->hasLoadErrors();

    if (ok) return 0;
    else return -1;
}

int ph_page_is_loaded(void *page) {
    Page *p = (Page*)page;
    if (p->isLoaded()) {
        return 0;
    } else {
        return -1;
    }
}

char* ph_page_to_html(void *page) {
    Page *p = (Page*)page;

    QByteArray data = p->toHtml();
    char *result_data = new char[data.size() + 1];
    qstrncpy(result_data, data.data(), data.size() + 1);

    return result_data;
}


char* ph_page_evaluate_javascript(void *page, char *javascript) {
    Page *p = (Page*)page;

    QString js(javascript);
    QByteArray data = p->evaluateJavaScript(js);

    char *result_data = new char[data.size() + 1];
    qstrncpy(result_data, data.data(), data.size() + 1);
    return result_data;
}

void* ph_page_capture_image(void *page, const char *format, int quality) {
    Page *p = (Page*)page;
    QByteArray image_data = p->captureImage(format, quality);

    Image *image = new Image(p);
    image->setFormat(format);
    image->setQuality(quality);
    image->setData(image_data);

    return image;
}

int64_t ph_image_get_size(void *image) {
    Image *img = (Image*)image;
    return img->size();
}

const char * ph_image_get_format(void *image) {
    Image *img = (Image*)image;
    return img->format().data();
}

void ph_image_get_bytes(void *image, void *buffer, int64_t size) {
    Image *img = (Image*)image;
    std::memcpy(buffer, img->data(), size);
}

void ph_image_free(void *image) {
    Image *img = (Image*)image;
    delete img;
}

void* ph_page_find_first(void *page, const char *selector) {
    Page *p = (Page*)page;
    QWebElement element = p->findFirstElement(QString::fromUtf8(selector));
    WebElement *elm = new WebElement(element);
    return elm;
}

void ph_webelement_free(void *element) {
    WebElement *el = (WebElement*)element;
    delete el;
}

char* ph_webelement_tag_name(void *element) {
    WebElement *el = (WebElement*)element;
    return el->tagName().data();
}

char* ph_webelement_inner_html(void *element) {
    WebElement *el = (WebElement*)element;
    return el->toHtml().data();
}

char* ph_webelement_inner_text(void *element) {
    WebElement *el = (WebElement*)element;
    return el->toText().data();
}

int32_t ph_webelement_is_null(void *element) {
    WebElement *el = (WebElement*)element;
    if (el->isNull()) {
        return 0;
    } else {
        return -1;
    }
}

}
