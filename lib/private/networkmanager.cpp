#include "networkmanager.hpp"
#include "cookiejar.hpp"
#include "context.hpp"

namespace ph {

NetworkManager::NetworkManager(QObject *parent): QNetworkAccessManager(parent) {
    setCookieJar(CookieJar::instance());
    m_authAttempts = 0;
    m_maxAuthAttempts = 3;

    connect(this, &NetworkManager::authenticationRequired,
            this, &NetworkManager::provideAuthentication);
}

NetworkManager::~NetworkManager() {}

void NetworkManager::setCookieJar(QNetworkCookieJar *cookieJar) {
    QNetworkAccessManager::setCookieJar(cookieJar);
    cookieJar->setParent(Context::instance());
}

void NetworkManager::setAuthData(const QString &username, const QString &password) {
    m_username = username;
    m_password = password;
}

void NetworkManager::setRequestTimeout(int requestTimeout) {
    m_requestTimeout = requestTimeout;
}

void NetworkManager::provideAuthentication(QNetworkReply *reply, QAuthenticator *authenticator) {
    if (m_authAttempts++ < m_maxAuthAttempts) {
        authenticator->setUser(m_username);
        authenticator->setPassword(m_password);
    } else {
        m_authAttempts = 0;
        reply->close();
    }
}

}
