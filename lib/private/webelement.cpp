#include "webelement.hpp"
#include "eventprocessor.hpp"
#include "timeout.hpp"

namespace ph {

WebElement::WebElement(const QWebElement &element, QObject *parent): QObject(parent) {
    m_web_element = element;

    if (!m_web_element.isNull()) {
        connect(m_web_element.webFrame()->page(), &QWebPage::loadFinished, this, &WebElement::loadFinished);
    }
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

QVariant WebElement::evaluateJavaScript(const QString &js, bool expectLoad, int timeout) {
    QVariant result = m_web_element.evaluateJavaScript(js);

    Timeout t(&m_loop, timeout);
    EventProcessor ep;

    t.start();
    ep.start();

    if (expectLoad) {
        m_loop.exec();
    }

    ep.stop();
    return result;
}

QStringList WebElement::getClasses() {
    return m_web_element.classes();
}

QStringList WebElement::getAttributeNames() {
    return m_web_element.attributeNames();
}

QString WebElement::getAttribute(const QString &attrname) {
    return m_web_element.attribute(attrname);
}

void WebElement::addClass(const QString &classname) {
    m_web_element.addClass(classname);
}

bool WebElement::hasClass(const QString &classname) {
    return m_web_element.hasClass(classname);
}

void WebElement::removeClass(const QString &classname) {
    m_web_element.removeClass(classname);
}

void WebElement::append(const QString &html) {
    m_web_element.appendInside(html);
}

void WebElement::append(WebElement *element) {
    m_web_element.appendInside(element->internalElement());
}

void WebElement::appendAfter(const QString &html) {
    m_web_element.appendOutside(html);
}

void WebElement::appendAfter(WebElement *element) {
    m_web_element.appendOutside(element->internalElement());
}

bool WebElement::hasAttribute(const QString &attrname) {
    return m_web_element.hasAttribute(attrname);
}

bool WebElement::hasAttributes() {
    return m_web_element.hasAttributes();
}

void WebElement::setAttribute(const QString &attrname, const QVariant &value) {
    m_web_element.setAttribute(attrname, value.toString());
}

void WebElement::removeAttribute(const QString &attrname) {
    m_web_element.removeAttribute(attrname);
}

void WebElement::replace(const QString &html) {
    m_web_element.replace(html);
}

void WebElement::replace(WebElement *element) {
    m_web_element.replace(element->internalElement());
}

void WebElement::wrap(const QString &html) {
    m_web_element.encloseWith(html);
}

void WebElement::wrap(WebElement *element) {
    m_web_element.encloseWith(element->internalElement());
}

void WebElement::removeAllChildren() {
    m_web_element.removeAllChildren();
}

void WebElement::removeFromDocument() {
    m_web_element.removeFromDocument();
}

QWebElement WebElement::takeFromDocument() {
    return m_web_element.takeFromDocument();
}

QWebElement WebElement::prev() {
    return m_web_element.previousSibling();
}

QWebElement WebElement::next() {
    return m_web_element.nextSibling();
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

QWebElement WebElement::internalElement() {
    return m_web_element;
}

void WebElement::loadFinished(bool ok) {
    m_loop.quit();
}

}
