#ifndef PHANTOMPY_CONTEXT_HPP
#define PHANTOMPY_CONTEXT_HPP

#include <QtCore>
#include <QtWebKit>
#include <QtWidgets>

//! Initial point for all engine execution.
/*! Some Qt features requires one `QCoreApplication` global instance.
 *  This class manage a correct creation and removing of
 *  global `QCoreApplication` instance. It should be used with smart
 *  pointers for correct resource managing. */

namespace ph {

class Context: public QObject {
public:
    Context(QObject *parent=0);
    ~Context();

    static Context* instance();
    static void clerInstance();

private:
    QApplication *app;
};

}

#endif
