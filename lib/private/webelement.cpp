#include "webelement.hpp"

namespace ph {

WebElement::WebElement(const QWebElement &element, QObject *parent): QObject(parent) {
    m_web_element = element;
}

WebElement::~WebElement() {}

bool WebElement::isNull() {
    return m_web_element.isNull();
}

QString WebElement::tagName() {
    return m_web_element.tagName();
}

QString WebElement::toHtml() {
    return m_web_element.toInnerXml();
}

QString WebElement::toText() {
    return m_web_element.toPlainText();
}

QString WebElement::evaluateJavaScript(const QString &data) {
    QVariant result = m_web_element.evaluateJavaScript(data);
    return result.toString();
}

QByteArray WebElement::getClasses() {
    return m_web_element.classes().join(" ").toUtf8();
}

QByteArray WebElement::getAttributes() {
    return m_web_element.attributeNames().join(" ").toUtf8();
}

bool WebElement::hasClass(const QString &classname) {
    return m_web_element.hasClass(classname);
}

bool WebElement::hasAttribute(const QString &attrname) {
    return m_web_element.hasAttribute(attrname);
}

bool WebElement::hasAttributes() {
    return m_web_element.hasAttributes();
}

void WebElement::removeClass(const QString &classname) {
    m_web_element.removeClass(classname);
}

void WebElement::removeAttribute(const QString &attrname) {
    m_web_element.removeAttribute(attrname);
}

void WebElement::setText(const QString &text) {
    m_web_element.setPlainText(text);
}

void WebElement::setHtml(const QString &html) {
    m_web_element.setInnerXml(html);
}

QWebElementCollection WebElement::findAll(const QString &selector) {
    return m_web_element.findAll(selector);
}


}
