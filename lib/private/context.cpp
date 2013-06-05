#include "context.hpp"

namespace ph {

static Context *contextInstance = NULL;

Context::Context(QObject *parent):QObject(parent) {
    char *argv[] = {"hello"};
    int argc = 1;

    p_app = new QApplication(argc, argv);
    setDefaultSettings();
}

Context::~Context() {
    delete p_app;
}

Context* Context::instance() {
    if (contextInstance == NULL) {
        contextInstance = new Context();
    }

    return contextInstance;
}

void Context::clerInstance() {
    if (contextInstance != NULL) {
        delete contextInstance;
        contextInstance = NULL;
    }
}

void Context::initializeEventTimer() {
#ifdef PHANTOMPY_QT4
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(handleTimeout()));
#else
    connect(&m_timer, &QTimer::timeout, this, &Context::handleTimeout);
#endif

#ifndef PHANTOMPY_QT4
    m_timer.setTimerType(Qt::CoarseTimer);
#endif
    m_timer.setInterval(300);

    m_timer.start();
}

void Context::setMaximumPagesInCache(int pages) {
   QWebSettings::setMaximumPagesInCache(pages);
}

void Context::setObjectCacheCapacities(int cacheMinDeadCapacity, int cacheMaxDead, int totalCapacity) {
   QWebSettings::setObjectCacheCapacities(cacheMinDeadCapacity, cacheMaxDead, totalCapacity);
}

void Context::clearMemoryCaches() {
    QWebSettings::clearMemoryCaches();
}

void Context::setConfig(const Settings &key, const QVariant &value) {
    m_settings[key] = value;
}

QVariant Context::getConfig(const Settings &key) {
    return m_settings[key];
}

void Context::setDefaultSettings() {
    m_settings[ph::LoadImages] = QVariant::fromValue(true);
    m_settings[ph::Javascript] = QVariant::fromValue(true);
    m_settings[ph::DnsPrefetching] = QVariant::fromValue(true);
    m_settings[ph::Plugins] = QVariant::fromValue(false);
    m_settings[ph::PrivateBrowsing] = QVariant::fromValue(false);
    m_settings[ph::OfflineStorageDB] = QVariant::fromValue(true);
    m_settings[ph::OfflineAppCache] = QVariant::fromValue(true);
    m_settings[ph::OfflineStorageQuota] = QVariant::fromValue(0);
    m_settings[ph::FrameFlattening] = QVariant::fromValue(true);
    m_settings[ph::LocalStorage] = QVariant::fromValue(true);
}

// Shortcuts

bool Context::settingsLoadImagesEnabled() {
    return m_settings[ph::LoadImages].toBool();
}

bool Context::settingsJavascriptEnabled() {
    return m_settings[ph::Javascript].toBool();
}

bool Context::settingsDnsPrefetchEnabled() {
    return m_settings[ph::DnsPrefetching].toBool();
}

bool Context::settingsPluginsEnabled() {
    return m_settings[ph::Plugins].toBool();
}

bool Context::settingsPrivateBrowsingEnabled() {
    return m_settings[ph::PrivateBrowsing].toBool();
}

bool Context::settingsFrameFlatteningEnabled() {
    return m_settings[ph::FrameFlattening].toBool();
}

bool Context::settingsLocalStorageEnabled() {
    return m_settings[ph::LocalStorage].toBool();
}

bool Context::settingsOfflineStorageDatabaseEnabled() {
    return m_settings[ph::OfflineStorageDB].toBool();
}

bool Context::settingsOfflineApplicationCacheEnabled() {
    return m_settings[ph::OfflineAppCache].toBool();
}

int Context::settingsofflineStorageDefaultQuota() {
    return m_settings[ph::OfflineStorageQuota].toInt();
}

void Context::handleTimeout() {
    qDebug() << "Handle Context Timeout";
    QApplication::processEvents();
}


}
