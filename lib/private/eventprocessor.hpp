#ifndef PHANTOMPY_EVENTPROCESSOR_HPP
#define PHANTOMPY_EVENTPROCESSOR_HPP

#include <QtCore>

namespace ph {

class EventProcessor: public QObject {
    Q_OBJECT

public:
    EventProcessor(QObject *parent=0);
    EventProcessor(int interval, QObject *parent=0);
    ~EventProcessor();

    void start();
    void stop();

private:
    QTimer *p_timer;
    int m_interval;

private slots:
    void handleTimeout();
};

}

#endif
