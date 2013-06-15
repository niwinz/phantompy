#include "timeout.hpp"

namespace ph {

Timeout::Timeout(QEventLoop *loop, int msecs, QObject *parent): QObject(parent) {
    p_loop = loop;

    p_timer = new QTimer();
    p_timer->setInterval(msecs);
    p_timer->setSingleShot(true);

    connect(p_timer, &QTimer::timeout, this, &Timeout::handleTimeout);

    p_timer->start();
}

Timeout::~Timeout() {
    if (p_timer->isActive()) {
        p_timer->stop();
    }
    delete p_timer;
}

void Timeout::handleTimeout() {
    p_loop->quit();
}

}
