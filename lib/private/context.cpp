#include "context.hpp"

namespace ph {

static Context *contextInstance = NULL;

Context::Context(QObject *parent):QObject(parent) {
   char *argv;
   int argc = 1;

   p_app = new QApplication(argc, &argv);
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
    m_settings[Settings::LoadImages] = QVariant::fromValue(true);
    m_settings[Settings::Javascript] = QVariant::fromValue(true);
    m_settings[Settings::DnsPrefetching] = QVariant::fromValue(true);
    m_settings[Settings::Plugins] = QVariant::fromValue(false);
    m_settings[Settings::PrivateBrowsing] = QVariant::fromValue(false);
    m_settings[Settings::OfflineStorageDB] = QVariant::fromValue(true);
    m_settings[Settings::OfflineAppCache] = QVariant::fromValue(true);
    m_settings[Settings::OfflineStorageQuota] = QVariant::fromValue(0);
    m_settings[Settings::FrameFlattening] = QVariant::fromValue(true);
    m_settings[Settings::LocalStorage] = QVariant::fromValue(true);
}

// Shortcuts

bool Context::settingsLoadImagesEnabled() {
    return m_settings[Settings::LoadImages].toBool();
}

bool Context::settingsJavascriptEnabled() {
    return m_settings[Settings::Javascript].toBool();
}

bool Context::settingsDnsPrefetchEnabled() {
    return m_settings[Settings::DnsPrefetching].toBool();
}

bool Context::settingsPluginsEnabled() {
    return m_settings[Settings::Plugins].toBool();
}

bool Context::settingsPrivateBrowsingEnabled() {
    return m_settings[Settings::PrivateBrowsing].toBool();
}

bool Context::settingsFrameFlatteningEnabled() {
    return m_settings[Settings::FrameFlattening].toBool();
}

bool Context::settingsLocalStorageEnabled() {
    return m_settings[Settings::LocalStorage].toBool();
}

bool Context::settingsOfflineStorageDatabaseEnabled() {
    return m_settings[Settings::OfflineStorageDB].toBool();
}

bool Context::settingsOfflineApplicationCacheEnabled() {
    return m_settings[Settings::OfflineAppCache].toBool();
}

int Context::settingsofflineStorageDefaultQuota() {
    return m_settings[Settings::OfflineStorageQuota].toInt();
}

}
