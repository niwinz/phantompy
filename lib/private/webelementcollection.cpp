#include "webelementcollection.hpp"

namespace ph {

WebElementCollection::WebElementCollection(const QWebElementCollection &collection, QObject *parent): QObject(parent) {
    m_elements = collection.toList();
}

WebElementCollection::~WebElementCollection() {}


QWebElement WebElementCollection::at(int index) {
    return m_elements.at(index);
}

int WebElementCollection::size() {
    return m_elements.size();
}

}
