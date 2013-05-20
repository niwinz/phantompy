#ifndef PHANTOMPY_PAGE_HPP
#define PHANTOMPY_PAGE_HPP

#include <QtCore>
#include <QtNetwork>
#include <QtWebKit>
#include <QtWebKitWidgets>

#include "networkmanagerproxy.hpp"

typedef QPair<QByteArray, QByteArray> HeaderPair;
typedef QList<HeaderPair> HeaderPairs;
typedef QHash<QString, HeaderPairs> HeadersCache;
typedef QHash<QString, QByteArray> ResponsesCache;


class Page: public QObject {
    Q_OBJECT

public:
    Page(QObject *parent=0);
    ~Page();

    void load(const QString &url);
    void setViewSize(int x, int y);

    bool isLoaded();
    bool hasLoadErrors();

    QWebFrame* mainFrame();
    QByteArray cookies();

    // Methods for get information about
    // background requests.
    QByteArray requestedUrls();
    QByteArray requestData(const QString &url);
    QByteArray requestHeaders(const QString &url);

private:
    bool m_loaded;
    bool m_error;

    QUrl m_mainUrl;
    QEventLoop m_eventLoop;
    QWebPage m_page;
    QSize m_viewSize;

    SyncNetworkManagerProxy m_nmProxy;

    QSet<QString> m_requestedUrls;
    HeadersCache m_headersCache;
    ResponsesCache m_responsesCache;

    QNetworkAccessManager m_networkManager;

private slots:
    void loadFinished(bool ok);
    void replyReceived(QNetworkReply *reply);
};

#endif
