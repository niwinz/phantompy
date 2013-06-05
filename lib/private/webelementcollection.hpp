#ifndef PHANTOMPY_WEBELEMENTCOLLECTION_HPP
#define PHANTOMPY_WEBELEMENTCOLLECTION_HPP

#include <QtCore>
#include <QtWebKit>
#ifndef PHANTOMPY_QT4
#include <QtWebKitWidgets>
#endif

namespace ph {

class WebElementCollection: public QObject {
    Q_OBJECT

public:
    WebElementCollection(const QWebElementCollection &collection, QObject *parent=0);
    ~WebElementCollection();

    QWebElement at(int index);
    int size();

private:
    QList<QWebElement> m_elements;

};

}


#endif
