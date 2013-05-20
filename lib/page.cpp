#include "page.hpp"

Page::Page(QObject *parent):QObject(parent) {
    m_page.setNetworkAccessManager(&m_networkManager);
    m_page.settings()->setAttribute(QWebSettings::LocalContentCanAccessFileUrls, true);
    m_page.settings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, true);
    //m_page.settings()->setAttribute(QWebSettings::PrivateBrowsingEnabled, true);

    connect(&m_page, SIGNAL(loadFinished(bool)), this, SLOT(loadFinished(bool)));
    connect(m_page.networkAccessManager(), SIGNAL(finished(QNetworkReply*)),
                this, SLOT(replyReceived(QNetworkReply*)));

    m_loaded = false;
    m_error = false;
}

Page::~Page() {}

void Page::load(const QString &_url) {
    m_mainUrl = QUrl::fromUserInput(_url);

    m_page.mainFrame()->load(m_mainUrl);
    m_page.mainFrame()->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);
    m_page.mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
    m_page.setViewportSize(m_viewSize);

    m_eventLoop.exec();
}

void Page::setViewSize(int x, int y) {
    this->m_viewSize = QSize(x, y);
}

void Page::loadFinished(bool ok) {
    m_eventLoop.quit();
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

void Page::replyReceived(QNetworkReply *reply) {
    if (reply->url() != m_mainUrl) {
        qDebug() << reply->url();
        m_requestedUrls.append(reply->url().toString());
    }
}

QByteArray Page::requestedUrls() {
    QJsonArray urls;

    for(auto i=m_requestedUrls.cbegin(); i != m_requestedUrls.cend(); ++i) {
        urls.append(QJsonValue((*i)));
    }

    return QJsonDocument(urls).toJson();
}
