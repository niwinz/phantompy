#include "phantompy.hpp"
#include "qjson/serializer.h"
#include "qjson/parser.h"
#include "private/eventprocessor.hpp"
#include "private/timeout.hpp"
#include "private/cookiejar.hpp"
#include "private/context.hpp"
#include "private/page.hpp"
#include "private/frame.hpp"
#include "private/image.hpp"
#include "private/webelement.hpp"
#include "private/webelementcollection.hpp"

char* _bytearray_to_char_ptr(const QByteArray &data) {
    char *resultData = new char[data.size() + 1];
    qstrncpy(resultData, data.data(), data.size() + 1);

    return resultData;
}

char* _qvariant_to_json_char_ptr(const QVariant &data) {
    QJson::Serializer serializer;
    bool ok;

    return _bytearray_to_char_ptr(serializer.serialize(data, &ok));
}

extern "C" {

/******* Context *******/

void* ph_context_init() {
    return ph::Context::instance();
}

void ph_context_free() {
    ph::Context::clerInstance();
}


void ph_context_process_events(int timeout) {
    QEventLoop ev_loop;

    ph::EventProcessor ep(10);
    ph::Timeout t(&ev_loop, timeout);

    ep.start();
    t.start();

    ev_loop.exec();
    ep.stop();
}


void ph_free_charptr(char *ptr) {
    delete [] ptr;
}

void ph_context_set_boolean_config(int key, int value) {
    ph::Context::instance()->setConfig(ph::Settings(key), QVariant::fromValue(!!value));
}

void ph_context_set_int_config(int key, int value) {
    ph::Context::instance()->setConfig(ph::Settings(key), QVariant::fromValue(value));
}

int32_t ph_context_get_boolean_config(int key) {
    return (int32_t)ph::Context::instance()->getConfig(ph::Settings(key)).toBool();
}

int32_t ph_context_get_int_config(int key) {
    return ph::Context::instance()->getConfig(ph::Settings(key)).toInt();
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

char* ph_context_get_all_cookies() {
    QJson::Serializer serializer;
    bool ok;

    QVariantList cookies = ph::CookieJar::instance()->getAllCookies();
    return _bytearray_to_char_ptr(serializer.serialize(cookies, &ok));
}

void ph_context_set_cookies(const char *cookies) {
    QJsonArray cookiesArray = QJsonDocument::fromJson(QByteArray(cookies)).array();
    QVariantList cookiesList = cookiesArray.toVariantList();

    ph::CookieJar::instance()->addCookiesFromMapList(cookiesList);
}

void ph_context_clear_cookies() {
    ph::CookieJar::instance()->clearCookies();
}


/******* Page *******/

void* ph_page_create() {
    ph::Page *p = new ph::Page();
    return p;
}

void ph_page_free(void *page) {
    ph::Page *p = (ph::Page*)page;
    p->deleteLater();
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


void ph_page_set_initial_cookies(void *page, const char *cookies) {
    ph::Page *p = static_cast<ph::Page*>(page);

    QJson::Parser parser;
    bool ok;

    QByteArray jsonData(cookies);
    QVariant cookiesData = parser.parse(jsonData, &ok);

    p->setInitialCookies(cookiesData.toList());
}


char* ph_page_get_cookies(void *page) {
    ph::Page *p = static_cast<ph::Page*>(page);
    QVariantList cookiesList = p->getCookies();

    QJson::Serializer serializer;
    bool ok;

    return _bytearray_to_char_ptr(serializer.serialize(cookiesList, &ok));
}


char* ph_page_get_requested_urls(void *page) {
    ph::Page *p = (ph::Page*)page;
    QSet<QString> urlsList = p->requestedUrls();

    QVariantList urls;
    QSet<QString>::const_iterator i;

    for(i=urlsList.cbegin(); i != urlsList.cend(); ++i) {
        urls << QVariant::fromValue((*i));
    }

    QJson::Serializer serializer;
    bool ok;

    return _bytearray_to_char_ptr(serializer.serialize(urls, &ok));
}

char* ph_page_get_reply_by_url(void *page, const char *url) {
    ph::Page *p = static_cast<ph::Page*>(page);
    QVariantMap response = p->getResponseByUrl(QString::fromUtf8(url));

    QJson::Serializer serializer;
    bool ok;

    return _bytearray_to_char_ptr(serializer.serialize(response, &ok));
}


void ph_page_go_back(void *page) {
    ph::Page *p = static_cast<ph::Page*>(page);
    p->history()->back();
}

void ph_page_go_forward(void *page) {
    ph::Page *p = static_cast<ph::Page*>(page);
    p->history()->forward();
}

/****** Frame ******/

void* ph_page_main_frame(void *page) {
    ph::Page *p = (ph::Page*)page;
    ph::Frame *f = new ph::Frame(p->mainFrame());
    return f;
}

void ph_frame_free(void *frame) {
    ph::Frame *f = (ph::Frame*)frame;
    f->deleteLater();
}

char* ph_frame_to_html(void *frame) {
    ph::Frame *f = (ph::Frame*)frame;
    return _bytearray_to_char_ptr(f->toHtml().toUtf8());
}

char* ph_frame_evaluate_javascript(void *frame, char *javascript, int expect_load, int timeout) {
    ph::Frame *f = (ph::Frame*)frame;

    QString js = QString::fromUtf8(javascript);
    return _qvariant_to_json_char_ptr(f->evaluateJavaScript(js, !!expect_load, timeout));
}

void* ph_frame_find_first(void *frame, const char *selector) {
    ph::Frame *f = (ph::Frame*)frame;
    QWebElement element = f->findFirstElement(QString::fromUtf8(selector));
    ph::WebElement *el = new ph::WebElement(element);
    return el;
}

void* ph_frame_find_all(void *frame, const char *selector) {
    ph::Frame *f = static_cast<ph::Frame*>(frame);

    QWebElementCollection collection = f->findAll(QString::fromUtf8(selector));
    ph::WebElementCollection *c = new ph::WebElementCollection(collection);
    return c;
}

char* ph_frame_get_url(void *frame) {
    ph::Frame *f = static_cast<ph::Frame*>(frame);
    return _bytearray_to_char_ptr(f->getUrl().toUtf8());
}

void ph_frame_set_url(void *frame, const char *url) {
    ph::Frame *f = static_cast<ph::Frame*>(frame);
    f->setUrl(QString::fromUtf8(url));
}

void ph_frame_load(void *frame, const char *url) {
    ph::Frame *f = static_cast<ph::Frame*>(frame);
    f->load(QString::fromUtf8(url));
}

/****** Web Element Collection *******/

int32_t ph_webcollection_size(void *collection) {
    ph::WebElementCollection *c = static_cast<ph::WebElementCollection*>(collection);
    return c->size();
}

void* ph_webcollection_get_webelement(void *collection, int32_t index) {
    ph::WebElementCollection *c = static_cast<ph::WebElementCollection*>(collection);
    QWebElement element = c->at(index);
    ph::WebElement *el = new ph::WebElement(element);
    return el;
}

void ph_webcollection_free(void *collection) {
    ph::WebElementCollection *c = static_cast<ph::WebElementCollection*>(collection);
    c->deleteLater();
}

/******* Frame Image *********/

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

const char* ph_image_get_format(void *image) {
    ph::Image *img = (ph::Image*)image;
    return img->format().data();
}

void ph_image_get_bytes(void *image, void *buffer, int64_t size) {
    ph::Image *img = (ph::Image*)image;
    std::memcpy(buffer, img->data(), size);
}

void ph_image_free(void *image) {
    ph::Image *img = (ph::Image*)image;
    img->deleteLater();
}

/****** Web Elements ******/

void ph_webelement_free(void *element) {
    ph::WebElement *el = static_cast<ph::WebElement*>(element);
    el->deleteLater();
}

void* ph_webelement_find_all(void *element, const char *selector) {
    ph::WebElement *el = static_cast<ph::WebElement*>(element);
    QWebElementCollection collection = el->findAll(QString::fromUtf8(selector));
    ph::WebElementCollection *c = new ph::WebElementCollection(collection);
    return c;
}

char* ph_webelement_tag_name(void *element) {
    ph::WebElement *el = static_cast<ph::WebElement*>(element);
    return _bytearray_to_char_ptr(el->tagName().toUtf8());
}

char* ph_webelement_inner_html(void *element) {
    ph::WebElement *el = static_cast<ph::WebElement*>(element);
    return _bytearray_to_char_ptr(el->toHtml().toUtf8());
}

char* ph_webelement_inner_text(void *element) {
    ph::WebElement *el = static_cast<ph::WebElement*>(element);
    return _bytearray_to_char_ptr(el->toText().toUtf8());
}


char* ph_webelement_get_classes(void *element) {
    ph::WebElement *el = static_cast<ph::WebElement*>(element);
    QByteArray data = el->getClasses().join(" ").toUtf8();

    return _bytearray_to_char_ptr(data);
}

char* ph_webelement_get_attrnames(void *element) {
    ph::WebElement *el = static_cast<ph::WebElement*>(element);
    QByteArray data = el->getAttributeNames().join(" ").toUtf8();

    return _bytearray_to_char_ptr(data);
}

char* ph_webelement_get_attr(void *element, const char *attrname) {
    ph::WebElement *el = static_cast<ph::WebElement*>(element);
    QByteArray data = el->getAttribute(QString::fromUtf8(attrname)).toUtf8();

    return _bytearray_to_char_ptr(data);
}

int32_t ph_webelement_has_class(void *element, const char *classname) {
    ph::WebElement *el = static_cast<ph::WebElement*>(element);
    if (el->hasClass(QString::fromUtf8(classname))) {
        return 0;
    } else {
        return -1;
    }
}

int32_t ph_webelement_has_attr(void *element, const char *attrname) {
    ph::WebElement *el = static_cast<ph::WebElement*>(element);
    if (el->hasAttribute(QString::fromUtf8(attrname))) {
        return 0;
    } else {
        return -1;
    }
}

int32_t ph_webelement_has_attrs(void *element) {
    ph::WebElement *el = static_cast<ph::WebElement*>(element);
    if (el->hasAttributes()) {
        return 0;
    } else {
        return -1;
    }
}

int32_t ph_webelement_is_null(void *element) {
    ph::WebElement *el = static_cast<ph::WebElement*>(element);
    if (el->isNull()) {
        return 0;
    } else {
        return -1;
    }
}

void ph_webelement_remove_class(void *element, const char *classname) {
    ph::WebElement *el = static_cast<ph::WebElement*>(element);
    el->removeClass(QString::fromUtf8(classname));
}

void ph_webelement_remove_attr(void *element, const char *attrname) {
    ph::WebElement *el = static_cast<ph::WebElement*>(element);
    el->removeAttribute(QString::fromUtf8(attrname));
}

void ph_webelement_add_class(void *element, const char *classname) {
    ph::WebElement *el = static_cast<ph::WebElement*>(element);
    el->addClass(QString::fromUtf8(classname));
}

void ph_webelement_set_attr(void *element, const char *attrname, const char *value) {
    ph::WebElement *el = static_cast<ph::WebElement*>(element);
    el->setAttribute(QString::fromUtf8(attrname), QVariant::fromValue(QString::fromUtf8(value)));
}

void ph_webelement_append_html(void *element, const char *htmldata) {
    ph::WebElement *el = static_cast<ph::WebElement*>(element);
    el->append(QString::fromUtf8(htmldata));
}

void ph_webelement_append_element(void *element, void *element2) {
    ph::WebElement *el = static_cast<ph::WebElement*>(element);
    ph::WebElement *el2 = static_cast<ph::WebElement*>(element2);
    el->append(el2);
}

void ph_webelement_append_html_after(void *element, const char *htmldata) {
    ph::WebElement *el = static_cast<ph::WebElement*>(element);
    el->appendAfter(QString::fromUtf8(htmldata));
}

void ph_webelement_append_element_after(void *element, void *element2) {
    ph::WebElement *el = static_cast<ph::WebElement*>(element);
    ph::WebElement *el2 = static_cast<ph::WebElement*>(element2);
    el->appendAfter(el2);
}

void ph_webelement_replace_with_html(void *element, const char *htmldata) {
    ph::WebElement *el = static_cast<ph::WebElement*>(element);
    el->replace(QString::fromUtf8(htmldata));
}

void ph_webelement_replace_with_element(void *element, void *element2) {
    ph::WebElement *el = static_cast<ph::WebElement*>(element);
    ph::WebElement *el2 = static_cast<ph::WebElement*>(element2);
    el->replace(el2);
}

void ph_webelement_remove_all_child_elements(void *element) {
    ph::WebElement *el = static_cast<ph::WebElement*>(element);
    el->removeAllChildren();
}

void ph_webelement_remove_from_document(void *element) {
    ph::WebElement *el = static_cast<ph::WebElement*>(element);
    el->removeFromDocument();
}

void* ph_webelement_take_from_document(void *element) {
    ph::WebElement *el = static_cast<ph::WebElement*>(element);
    QWebElement elref = el->takeFromDocument();
    ph::WebElement *el2 = new ph::WebElement(elref);
    return el2;
}

void ph_webelement_wrap_with_html(void *element, const char *htmldata) {
    ph::WebElement *el = static_cast<ph::WebElement*>(element);
    el->wrap(QString::fromUtf8(htmldata));
}

void ph_webelement_wrap_with_element(void *element, void *element2) {
    ph::WebElement *el = static_cast<ph::WebElement*>(element);
    ph::WebElement *el2 = static_cast<ph::WebElement*>(element2);
    el->wrap(el2);
}

void* ph_webelement_previous(void *element) {
    ph::WebElement *el = static_cast<ph::WebElement*>(element);
    QWebElement elm = el->prev();
    return new ph::WebElement(elm);
}

void* ph_webelement_next(void *element) {
    ph::WebElement *el = static_cast<ph::WebElement*>(element);
    QWebElement elm = el->next();
    return new ph::WebElement(elm);
}

char* ph_webelement_evaluate_javascript(void *element, const char *javascript, int expect_load, int timeout) {
    ph::WebElement *el = static_cast<ph::WebElement*>(element);

    QString js = QString::fromUtf8(javascript);
    return _qvariant_to_json_char_ptr(el->evaluateJavaScript(js, !!expect_load, timeout));
}

}
