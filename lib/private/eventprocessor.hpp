#ifndef PHANTOMPY_EVENTPROCESSOR_HPP
#define PHANTOMPY_EVENTPROCESSOR_HPP

#include <QtCore>

namespace ph {

class EventProcessor: public QObject {
    Q_OBJECT

public:
    EventProcessor(QObject *parent=0);
    ~EventProcessor();

private:
    QTimer *p_timer;

private slots:
    void handleTimeout();
};

}

#endif
