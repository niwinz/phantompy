#ifndef PHANTOMPY_CONTEXT_HPP
#define PHANTOMPY_CONTEXT_HPP

#include <QtCore>

//! Initial point for all engine execution.
/*! Some Qt features requires one `QCoreApplication` global instance.
 *  This class manage a correct creation and removing of
 *  global `QCoreApplication` instance. It should be used with smart
 *  pointers for correct resource managing. */

class Context: public QObject {
public:
    Context(QObject *parent=0): QObject(parent) {
        char *argv;
        int argc = 1;

        this->app = new QApplication(argc, &argv);
    }

    ~Context() {
        delete this->app;
    }

    QApplication *app;
};

#endif
