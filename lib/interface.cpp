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

char* ph_page_to_image_bytes(void *page, char *format, int quality) {
    Page *p = (Page*)page;
    std::shared_ptr<QBuffer> buffer = p->toImageBytes(format, quality);

    qDebug() << "BUFFER size" << buffer->size();
    qDebug() << "BUFFER size" << buffer->data().size();

    QByteArray buffer_ba = buffer->data();

    char *result_data = new char[buffer_ba.size()];
    std::memcpy(result_data, buffer_ba.constData(), buffer_ba.size());

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

}
