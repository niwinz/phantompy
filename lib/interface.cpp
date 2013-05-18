#include "interface.hpp"
#include "context.hpp"

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
    Page *p;
    bool ok;

    p = (Page*)page;
    p->load(QString::fromUtf8(url));

    ok = p->hasLoadErrors();

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

    QString html = p->toHtml();
    QByteArray data = html.toUtf8();

    char *result_data = new char[data.size() + 1];
    qstrncpy(result_data, data.data(), data.size() + 1);

    return result_data;
}

}
