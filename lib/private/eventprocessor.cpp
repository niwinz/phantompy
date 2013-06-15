#include "eventprocessor.hpp"
#include "context.hpp"

namespace ph {

EventProcessor::EventProcessor(QObject *parent): QObject(parent) {
    p_timer = new QTimer();
    p_timer->setInterval(100);
    p_timer->setSingleShot(false);

    connect(p_timer, &QTimer::timeout, this, &EventProcessor::handleTimeout);
    p_timer->start();
}

EventProcessor::EventProcessor(int interval, QObject *parent): QObject(parent) {
    p_timer = new QTimer();
    p_timer->setInterval(interval);
    p_timer->setSingleShot(false);

    connect(p_timer, &QTimer::timeout, this, &EventProcessor::handleTimeout);
    p_timer->start(interval);
}

EventProcessor::~EventProcessor() {
    p_timer->stop();
    delete p_timer;
}

void EventProcessor::handleTimeout() {
    Context::instance()->mutex()->lock();
    QApplication::processEvents();
    Context::instance()->mutex()->unlock();
}

}
