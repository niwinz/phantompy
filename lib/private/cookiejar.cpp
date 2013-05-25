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

}
