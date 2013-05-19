#include "page.hpp"

Page::Page(QObject *parent):QObject(parent) {
    connect(&m_page, SIGNAL(loadFinished(bool)), this, SLOT(loadFinished(bool)));
    connect(m_page.networkAccessManager(), SIGNAL(finished(QNetworkReply*)),
                this, SLOT(replyReceived(QNetworkReply*)));

    m_loaded = false;
    m_error = false;
}

Page::~Page() {}

void Page::load(const QString &_url) {
    QUrl url = QUrl::fromUserInput(_url);

    m_page.mainFrame()->load(url);
    m_page.mainFrame()->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);
    m_page.mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
    m_page.setViewportSize(m_view_size);

    m_event_loop.exec();
}

void Page::setViewSize(int x, int y) {
    this->m_view_size = QSize(x, y);
}

void Page::loadFinished(bool ok) {
    m_event_loop.quit();
    m_error = ok;
}

bool Page::isLoaded() {
    return m_loaded;
}

bool Page::hasLoadErrors() {
    return m_error;
}

QWebFrame* Page::mainFrame() {
    return m_page.mainFrame();
}

QByteArray Page::cookies() {
    QNetworkAccessManager *nm = m_page.networkAccessManager();
    QNetworkCookieJar *cj = nm->cookieJar();
    QUrl url = m_page.mainFrame()->url();

    QJsonObject cookies;
    foreach(QNetworkCookie c, cj->cookiesForUrl(url)) {
        QJsonValue value(QString::fromUtf8(c.value()));
        cookies.insert(QString::fromUtf8(c.name()), value);
    }

    return QJsonDocument(cookies).toJson();
}

void Page::replyReceived(QNetworkReply *reply) {}
