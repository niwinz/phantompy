#ifndef PHANTOMPY_PAGE_HPP
#define PHANTOMPY_PAGE_HPP

#include <QtCore>
#include <QtNetwork>
#include <QtWebKit>
#include <QtWebKitWidgets>

#include "networkmanager.hpp"
#include "networkmanagerproxy.hpp"

namespace ph {

typedef QHash<QString, QVariantMap> ResponsesMap;
typedef QHash<QString, QString> Cookies;


class Page: public QObject {
    Q_OBJECT

public:
    Page(QObject *parent=0);
    ~Page();

    void load(const QString &url);
    void setViewSize(int x, int y);
    void setInitialCookies(const QVariantList &cookies);
    QVariantList getCookies();

    bool isLoaded();
    bool hasLoadErrors();

    QWebFrame* mainFrame();
    QWebHistory* history();

    QSet<QString> requestedUrls();
    QVariantMap getResponseByUrl(const QString &url);

private:
    bool m_loaded;
    bool m_error;

    QUrl m_mainUrl;
    QEventLoop m_eventLoop;
    QWebPage m_page;
    QSize m_viewSize;
    QVariantList m_initialCookies;

    QSet<QString> m_requestedUrls;
    ResponsesMap m_responsesCache;

    SyncNetworkManagerProxy m_nmProxy;
    NetworkManager m_networkManager;

    void applySettings();

private slots:
    void loadFinished(bool ok);
    void replyReceived(const QVariantMap &reply);
};

}

#endif
