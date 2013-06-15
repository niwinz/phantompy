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

EventProcessor::~EventProcessor() {
    p_timer->stop();
    delete p_timer;
}

void EventProcessor::handleTimeout() {
    QApplication::processEvents();
}

}
