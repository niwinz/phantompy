#include "phantompy.hpp"
#include "private/context.hpp"
#include "private/page.hpp"
#include "private/frame.hpp"
#include "private/image.hpp"
#include "private/webelement.hpp"

extern "C" {

/******* Context *******/

void* ph_context_init() {
    return ph::Context::instance();
}

void ph_context_free(void *ctx) {
    ph::Context::clerInstance();
}

void ph_context_set_boolean_config(int key, int value) {
    ph::Context::instance()->setConfig(ph::Settings(key), QVariant::fromValue(!!value));
}

void ph_context_clear_memory_cache() {
    ph::Context::instance()->clearMemoryCaches();
}

void ph_context_set_object_cache_capacity(int i, int x, int z) {
    ph::Context::instance()->setObjectCacheCapacities(i, x, z);
}

void ph_context_set_max_pages_in_cache(int num) {
    ph::Context::instance()->setMaximumPagesInCache(num);
}

/******* Page *******/

void* ph_page_create() {
    ph::Page *p = new ph::Page();
    return p;
}

void ph_page_free(void *page) {
    ph::Page *p = (ph::Page*)page;
    delete p;
}

void ph_page_set_viewpoint_size(void *page, int x, int y) {
    ph::Page *p = (ph::Page*)page;
    p->setViewSize(x, y);
}

int ph_page_load(void *page, char *url) {
    ph::Page *p = (ph::Page*)page;
    p->load(QString::fromUtf8(url));

    bool ok = p->hasLoadErrors();

    if (ok) return 0;
    else return -1;
}

int ph_page_is_loaded(void *page) {
    ph::Page *p = (ph::Page*)page;
    if (p->isLoaded()) {
        return 0;
    } else {
        return -1;
    }
}

char* ph_page_cookies(void *page) {
    ph::Page *p = (ph::Page*)page;
    ph::Cookies cookies = p->cookies();

    QJsonObject cookiesObj;
    for(auto i=cookies.cbegin(); i!=cookies.cend(); ++i) {
        cookiesObj.insert(i.key(), QJsonValue(i.value()));
    }

    QByteArray cookiesData = QJsonDocument(cookiesObj).toJson();
    char *resultData = new char[cookiesData.size() + 1];

    qstrncpy(resultData, cookiesData.data(), cookiesData.size() + 1);
    return resultData;
}

char* ph_page_requested_urls(void *page) {
    ph::Page *p = (ph::Page*)page;
    QSet<QString> urlsList = p->requestedUrls();

    QJsonArray urls;
    for(auto i=urlsList.cbegin(); i != urlsList.cend(); ++i) {
        urls.append(QJsonValue((*i)));
    }

    QByteArray requestedUrls = QJsonDocument(urls).toJson();
    char *resultData = new char[requestedUrls.size() + 1];

    qstrncpy(resultData, requestedUrls.data(), requestedUrls.size() + 1);
    return resultData;
}

//char* ph_page_request_headers(void *page, const char* url) {
//    Page *p = (Page*)page;
//
//    QJsonObject hobj;
//
//    for(auto i=headers.cbegin(); i != headers.cend(); ++i) {
//        QString key = QString::fromUtf8( (*i).first );
//        QString value = QString::fromUtf8( (*i).second );
//
//        hobj.insert(key, QJsonValue(value));
//    }
//
//    return QJsonDocument(hobj).toJson();
//}

void* ph_page_main_frame(void *page) {
    ph::Page *p = (ph::Page*)page;
    ph::Frame *f = new ph::Frame(p->mainFrame());
    return f;
}

void ph_frame_free(void *frame) {
    ph::Frame *f = (ph::Frame*)frame;
    delete f;
}


char* ph_frame_to_html(void *frame) {
    ph::Frame *f = (ph::Frame*)frame;

    QByteArray data = f->toHtml().toUtf8();
    char *resultData = new char[data.size() + 1];
    qstrncpy(resultData, data.data(), data.size() + 1);
    return resultData;
}


char* ph_frame_evaluate_javascript(void *frame, char *javascript) {
    ph::Frame *f = (ph::Frame*)frame;

    QString js(javascript);
    QByteArray data = f->evaluateJavaScript(js).toUtf8();

    char *resultData = new char[data.size() + 1];
    qstrncpy(resultData, data.data(), data.size() + 1);
    return resultData;
}

void* ph_frame_find_first(void *frame, const char *selector) {
    ph::Frame *f = (ph::Frame*)frame;
    QWebElement element = f->findFirstElement(QString::fromUtf8(selector));
    ph::WebElement *elm = new ph::WebElement(element);
    return elm;
}

void* ph_frame_capture_image(void *frame, const char *format, int quality) {
    ph::Frame *f = (ph::Frame*)frame;
    QByteArray image_data = f->captureImage(format, quality);

    ph::Image *image = new ph::Image(f);
    image->setFormat(format);
    image->setQuality(quality);
    image->setData(image_data);

    return image;
}

int64_t ph_image_get_size(void *image) {
    ph::Image *img = (ph::Image*)image;
    return img->size();
}

const char * ph_image_get_format(void *image) {
    ph::Image *img = (ph::Image*)image;
    return img->format().data();
}

void ph_image_get_bytes(void *image, void *buffer, int64_t size) {
    ph::Image *img = (ph::Image*)image;
    std::memcpy(buffer, img->data(), size);
}

void ph_image_free(void *image) {
    ph::Image *img = (ph::Image*)image;
    delete img;
}


void ph_webelement_free(void *element) {
    ph::WebElement *el = (ph::WebElement*)element;
    delete el;
}

char* ph_webelement_tag_name(void *element) {
    ph::WebElement *el = (ph::WebElement*)element;

    QByteArray data = el->tagName().toUtf8();
    char *resultData = new char[data.size() + 1];

    qstrncpy(resultData, data.data(), data.size() + 1);
    return resultData;
}

char* ph_webelement_inner_html(void *element) {
    ph::WebElement *el = (ph::WebElement*)element;
    QByteArray data = el->toHtml().toUtf8();
    char *resultData = new char[data.size() + 1];

    qstrncpy(resultData, data.data(), data.size() + 1);
    return resultData;
}

char* ph_webelement_inner_text(void *element) {
    ph::WebElement *el = (ph::WebElement*)element;
    QByteArray data = el->toText().toUtf8();
    char *resultData = new char[data.size() + 1];

    qstrncpy(resultData, data.data(), data.size() + 1);
    return resultData;
}

int32_t ph_webelement_has_class(void *element, const char *classname) {
    ph::WebElement *el = (ph::WebElement*)element;
    if (el->hasClass(QString::fromUtf8(classname))) {
        return 0;
    } else {
        return -1;
    }
}

int32_t ph_webelement_has_attr(void *element, const char *attrname) {
    ph::WebElement *el = (ph::WebElement*)element;
    if (el->hasAttribute(QString::fromUtf8(attrname))) {
        return 0;
    } else {
        return -1;
    }
}

int32_t ph_webelement_has_attrs(void *element) {
    ph::WebElement *el = (ph::WebElement*)element;
    if (el->hasAttributes()) {
        return 0;
    } else {
        return -1;
    }
}

int32_t ph_webelement_is_null(void *element) {
    ph::WebElement *el = (ph::WebElement*)element;
    if (el->isNull()) {
        return 0;
    } else {
        return -1;
    }
}

}
