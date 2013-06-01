#ifndef PHANTOMPY_NETWORKMANAGER_HPP
#define PHANTOMPY_NETWORKMANAGER_HPP

#include <QtCore>
#include <QtNetwork>

namespace ph {


class NetworkManager: public QNetworkAccessManager {
    Q_OBJECT

public:
    NetworkManager(QObject *parent);
    ~NetworkManager();

    void setCookieJar(QNetworkCookieJar *cookieJar);
    void setAuthData(const QString &username, const QString &password);
    void setRequestTimeout(int requestTimeout);

private:
    int m_requestTimeout;
    int m_authAttempts;
    int m_maxAuthAttempts;

    QString m_username;
    QString m_password;

signals:
    void replyReceived(const QVariantMap &reply);

protected:
    QNetworkReply *createRequest(Operation op, const QNetworkRequest &rq, QIODevice *data=0);

private slots:
    void provideAuthentication(QNetworkReply *reply, QAuthenticator *authenticator);
    void handleReadyReply();
    void handleTimeout();
};

}


#endif
