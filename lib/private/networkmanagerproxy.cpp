#include "networkmanagerproxy.hpp"

namespace ph {

SyncNetworkManagerProxy::SyncNetworkManagerProxy(QObject *parent): QObject(parent) {}
SyncNetworkManagerProxy::~SyncNetworkManagerProxy() {}

void SyncNetworkManagerProxy::setNetworkAccessManager(QNetworkAccessManager *manager) {
    p_manager = manager;
}

QNetworkReply* SyncNetworkManagerProxy::get(const QUrl &url) {
    return get(QNetworkRequest(url));
}

QNetworkReply* SyncNetworkManagerProxy::get(const QNetworkRequest &request) {
    QNetworkReply *reply = p_manager->get(request);

#ifdef PHANTOMPY_QT4
    connect(reply, SIGNAL(finished()), this, SLOT(finished()));
    m_eventLoop.exec();
#else
    QMetaObject::Connection connection = connect(reply, &QNetworkReply::finished,
                                                 this, &SyncNetworkManagerProxy::finished);
    m_eventLoop.exec();
    QObject::disconnect(connection);
#endif

    return reply;
}

void SyncNetworkManagerProxy::finished() {
    m_eventLoop.quit();
}

}
