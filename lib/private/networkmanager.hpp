#ifndef PHANTOMPY_NETWORKMANAGER_HPP
#define PHANTOMPY_NETWORKMANAGER_HPP

#include <QtCore>
#include <QtNetwork>


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

    QString m_username;
    QString m_password;

protected:
    QNetworkReply *createRequest(Operation op, const QNetworkRequest &rq, QIODevice *data=0);

private slots:
    void provideAuthentication(QNetworkReply *reply, QAuthenticator *authenticator);
    void handleReadyReply();
};


#endif
