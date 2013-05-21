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
    Cookies cookies = p->cookies();

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
    Page *p = (Page*)page;
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

}
