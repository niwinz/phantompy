#ifndef PHANTOMPY_PAGE_HPP
#define PHANTOMPY_PAGE_HPP

#include <QtCore>
#include <QtNetwork>
#include <QtWebKit>
#include <QtWebKitWidgets>


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
    QByteArray requestedUrls();

private:
    bool m_loaded;
    bool m_error;

    QUrl m_mainUrl;
    QEventLoop m_eventLoop;
    QWebPage m_page;
    QSize m_viewSize;

    QList<QString> m_requestedUrls;
    QNetworkAccessManager m_networkManager;

private slots:
    void loadFinished(bool ok);
    void replyReceived(QNetworkReply *reply);
};

#endif
