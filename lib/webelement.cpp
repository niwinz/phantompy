#include "webelement.hpp"

WebElement::WebElement(const QWebElement &element, QObject *parent): QObject(parent) {
    m_web_element = element;
}

WebElement::~WebElement() {}

bool WebElement::isNull() {
    return m_web_element.isNull();
}

QByteArray WebElement::tagName() {
    return m_web_element.tagName().toUtf8();
}

QByteArray WebElement::toHtml() {
    return m_web_element.toInnerXml().toUtf8();
}

QByteArray WebElement::toText() {
    return m_web_element.toPlainText().toUtf8();
}

QByteArray WebElement::evaluateJavaScript(const QByteArray &data) {
    QVariant result = m_web_element.evaluateJavaScript(QString::fromUtf8(data));
    return result.toString().toUtf8();
}

QByteArray WebElement::getClasses() {
    return m_web_element.classes().join(" ").toUtf8();
}

QByteArray WebElement::getAttributes() {
    return m_web_element.attributeNames().join(" ").toUtf8();
}

bool WebElement::hasClass(const QByteArray &classname) {
    return m_web_element.hasClass(QString::fromUtf8(classname));
}

bool WebElement::hasAttribute(const QByteArray &attrname) {
    return m_web_element.hasAttribute(QString::fromUtf8(attrname));
}

bool WebElement::hasAttributes() {
    return m_web_element.hasAttributes();
}
