#ifndef PHANTOMPY_CONTEXT_HPP
#define PHANTOMPY_CONTEXT_HPP

#include <QtCore>
#include <QtWebKit>
#include <QtWidgets>

#include "eventprocessor.hpp"

//! Initial point for all engine execution.
/*! Some Qt features requires one `QCoreApplication` global instance.
 *  This class manage a correct creation and removing of
 *  global `QCoreApplication` instance. It should be used with smart
 *  pointers for correct resource managing. */

namespace ph {

enum Settings {
    LoadImages = 1,
    Javascript,
    DnsPrefetching,
    Plugins,
    PrivateBrowsing,
    OfflineStorageDB,
    OfflineStorageQuota,
    OfflineAppCache,
    FrameFlattening,
    LocalStorage,
};

class Context: public QObject {
public:
    Context(QObject *parent=0);
    ~Context();

    static Context* instance();
    static void clerInstance();

    void setMaximumPagesInCache(int pages);
    void setObjectCacheCapacities(int cacheMinDeadCapacity, int cacheMaxDead, int totalCapacity);
    void clearMemoryCaches();

    void setConfig(const Settings &key, const QVariant &value);
    QVariant getConfig(const Settings &key);

    bool settingsLoadImagesEnabled();
    bool settingsJavascriptEnabled();
    bool settingsDnsPrefetchEnabled();
    bool settingsPluginsEnabled();
    bool settingsPrivateBrowsingEnabled();
    bool settingsFrameFlatteningEnabled();
    bool settingsLocalStorageEnabled();
    bool settingsOfflineStorageDatabaseEnabled();
    bool settingsOfflineApplicationCacheEnabled();

    int settingsofflineStorageDefaultQuota();

    QApplication* app();
    QMutex* mutex();

private:
    QApplication *p_app;
    EventProcessor *p_ep;
    QMutex *p_mutex;

    QTimer m_timer;
    QHash<Settings, QVariant> m_settings;

    void setDefaultSettings();
};

}

#endif
