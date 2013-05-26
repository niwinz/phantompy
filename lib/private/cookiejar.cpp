#include "cookiejar.hpp"
#include "context.hpp"

namespace ph {

static CookieJar *cookiesJarInstance = NULL;

CookieJar::CookieJar(QObject *parent): QNetworkCookieJar(parent) {}
CookieJar::~CookieJar() {}

CookieJar *CookieJar::instance() {
    if (cookiesJarInstance == NULL) {
        cookiesJarInstance = new CookieJar(Context::instance());
    }

    return cookiesJarInstance;
}

void CookieJar::addCookie(const QNetworkCookie &cookie, const QString &url) {
    bool ok = validateCookie(cookie, QUrl(url));
    if (ok) {
        QList<QNetworkCookie> cookiesList;
        cookiesList << cookie;

        setCookiesFromUrl(cookiesList, QUrl(url));
    } else {
        qWarning() << "CookieJar::addCookie: Rejected Cookie"
                   << cookie.toRawForm();
    }
}

void CookieJar::addCookieFromMap(const QVariantMap &cookie, const QString &url) {
    QNetworkCookie n_cookie;

    if (!cookie["name"].isNull() && !cookie["name"].toString().isEmpty() && !cookie["value"].isNull()) {
        n_cookie.setName(cookie["name"].toByteArray());
        n_cookie.setValue(cookie["value"].toByteArray());

        if (!cookie["domain"].isNull() && !cookie["domain"].toString().isEmpty()) {
            n_cookie.setDomain(cookie["domain"].toString());
        }

        if (!cookie["path"].isNull() || !cookie["path"].toString().isEmpty()) {
            n_cookie.setPath(cookie["path"].toString());
        }

        n_cookie.setHttpOnly(cookie["httponly"].isNull() ? false : cookie["httponly"].toBool());
        n_cookie.setSecure(cookie["secure"].isNull() ? false : cookie["secure"].toBool());

        if (!cookie["expires"].isNull()) {
            QDateTime n_expires = QDateTime::fromString(cookie["expires"].toString(), Qt::ISODate);
            if (n_expires.isValid()) {
                n_cookie.setExpirationDate(n_expires);
            }
        }

        addCookie(n_cookie, url);
    }
}

void CookieJar::addCookiesFromMapList(const QVariantList &cookies, const QString &url) {
    for(auto i=cookies.cbegin(); i!=cookies.cend(); ++i) {
        addCookieFromMap((*i).toMap(), url);
    }
}

}
