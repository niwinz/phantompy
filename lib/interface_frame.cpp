#include "interface.hpp"

extern "C" {

void* ph_page_main_frame(void *page) {
    Page *p = (Page*)page;
    Frame *f = new Frame(p->mainFrame());
    return f;
}

void ph_frame_free(void *frame) {
    Frame *f = (Frame*)frame;
    delete f;
}


char* ph_frame_to_html(void *frame) {
    Frame *f = (Frame*)frame;

    QByteArray data = f->toHtml();
    char *result_data = new char[data.size() + 1];
    qstrncpy(result_data, data.data(), data.size() + 1);
    return result_data;
}


char* ph_frame_evaluate_javascript(void *frame, char *javascript) {
    Frame *f = (Frame*)frame;

    QString js(javascript);
    QByteArray data = f->evaluateJavaScript(js);

    char *result_data = new char[data.size() + 1];
    qstrncpy(result_data, data.data(), data.size() + 1);
    return result_data;
}

void* ph_frame_find_first(void *frame, const char *selector) {
    Frame *f = (Frame*)frame;
    QWebElement element = f->findFirstElement(QString::fromUtf8(selector));
    WebElement *elm = new WebElement(element);
    return elm;
}

void* ph_frame_capture_image(void *frame, const char *format, int quality) {
    Frame *f = (Frame*)frame;
    QByteArray image_data = f->captureImage(format, quality);

    Image *image = new Image(f);
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

int32_t ph_webelement_has_class(void *element, const char *classname) {
    WebElement *el = (WebElement*)element;
    if (el->hasClass(QString::fromUtf8(classname))) {
        return 0;
    } else {
        return -1;
    }
}

int32_t ph_webelement_has_attr(void *element, const char *attrname) {
    WebElement *el = (WebElement*)element;
    if (el->hasAttribute(QString::fromUtf8(attrname))) {
        return 0;
    } else {
        return -1;
    }
}

int32_t ph_webelement_has_attrs(void *element) {
    WebElement *el = (WebElement*)element;
    if (el->hasAttributes()) {
        return 0;
    } else {
        return -1;
    }
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
