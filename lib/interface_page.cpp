#include "interface.hpp"
#include "page.hpp"

extern "C" {

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

char* ph_page_cookies(void *page) {
    Page *p = (Page*)page;
    QByteArray cookies = p->cookies();

    char *resultData = new char[cookies.size() + 1];
    qstrncpy(resultData, cookies.data(), cookies.size() + 1);

    return resultData;
}

char* ph_page_requested_urls(void *page) {
    Page *p = (Page*)page;
    QByteArray requestedUrls = p->requestedUrls();

    char *resultData = new char[requestedUrls.size() + 1];
    qstrncpy(resultData, requestedUrls.data(), requestedUrls.size() + 1);

    return resultData;
}

}
