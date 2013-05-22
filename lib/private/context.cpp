#include "context.hpp"

namespace ph {

static Context *contextInstance = NULL;

Context::Context(QObject *parent):QObject(parent) {
   char *argv;
   int argc = 1;

   this->app = new QApplication(argc, &argv);

   QWebSettings::setMaximumPagesInCache( 0 );
   QWebSettings::setObjectCacheCapacities( 0, 0, 0 );
   QWebSettings::clearMemoryCaches( );
}

Context::~Context() {
    delete this->app;
}

Context* Context::instance() {
    if (contextInstance == NULL) {
        contextInstance = new Context();
    }

    return contextInstance;
}

void Context::clerInstance() {
    if (contextInstance != NULL) {
        delete contextInstance;
        contextInstance = NULL;
    }
}

}
