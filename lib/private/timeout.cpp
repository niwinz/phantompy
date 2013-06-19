#include "timeout.hpp"

namespace ph {

Timeout::Timeout(QEventLoop *loop, int msecs, QObject *parent): QObject(parent) {
    p_timer = new QTimer();
    p_loop = loop;
    m_interval = msecs;
}

Timeout::~Timeout() {
    if (p_timer->isActive()) {
        p_timer->stop();
    }
    p_timer->deleteLater();
}

void Timeout::start() {
    p_timer->setInterval(m_interval);
    p_timer->setSingleShot(true);

    connect(p_timer, &QTimer::timeout, this, &Timeout::handleTimeout);
    p_timer->start();
}

void Timeout::handleTimeout() {
    p_loop->quit();
}

}
