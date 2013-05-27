#ifndef PHANTOMPY_NETWORK_TIMEOUT
#define PHANTOMPY_NETWORK_TIMEOUT

#include <QtCore>
#include <QtNetwork>

namespace ph {

class NetworkTimeoutTimer: public QTimer {
    Q_OBJECT
public:
    NetworkTimeoutTimer(QObject *parent=0);
    ~NetworkTimeoutTimer();

    QNetworkReply *reply;
};

}

#endif
