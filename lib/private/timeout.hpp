#ifndef PHANTOMPY_TIMEOUT_HPP
#define PHANTOMPY_TIMEOUT_HPP

#include <QtCore>

namespace ph {

class Timeout: public QObject {
    Q_OBJECT

public:
    Timeout(QEventLoop *loop, int msecs=5000, QObject *parent=0);
    ~Timeout();

    void start();

private:
    QTimer *p_timer;
    QEventLoop *p_loop;
    int m_interval;

private slots:
    void handleTimeout();
};

}

#endif
