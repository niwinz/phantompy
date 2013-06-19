#include "eventprocessor.hpp"
#include "context.hpp"

namespace ph {

EventProcessor::EventProcessor(QObject *parent): QObject(parent) {
    m_interval = 50;
    p_timer = new QTimer();
}

EventProcessor::EventProcessor(int interval, QObject *parent): QObject(parent) {
    m_interval = interval;
    p_timer = new QTimer();
}

EventProcessor::~EventProcessor() {
    if (p_timer->isActive()) {
        p_timer->stop();
    }

    p_timer->deleteLater();
}

void EventProcessor::start() {
    p_timer->setInterval(m_interval);
    p_timer->setSingleShot(false);

    connect(p_timer, &QTimer::timeout, this, &EventProcessor::handleTimeout);
    p_timer->start();
}

void EventProcessor::stop() {
    if (p_timer->isActive()) {
        p_timer->stop();
    }
}

void EventProcessor::handleTimeout() {
    Context::instance()->mutex()->lock();
    QApplication::processEvents();
    Context::instance()->mutex()->unlock();
}

}
