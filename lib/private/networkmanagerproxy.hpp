#ifndef PHANTOMPY_PARTIAL_REQUEST_HPP
#define PHANTOMPY_PARTIAL_REQUEST_HPP

#include <QtCore>
#include <QtNetwork>

namespace ph {

class SyncNetworkManagerProxy: public QObject {
    Q_OBJECT

public:
    SyncNetworkManagerProxy(QObject *parent=0);
    ~SyncNetworkManagerProxy();

    void setNetworkAccessManager(QNetworkAccessManager *manager);
    QNetworkReply* get(const QUrl &url);
    QNetworkReply* get(const QNetworkRequest &request);

private:
    QEventLoop m_eventLoop;
    QNetworkAccessManager *p_manager;


private slots:
    void finished();
};

}

#endif
