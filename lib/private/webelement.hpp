#ifndef PHANTOMPY_WEBELEMENT_HPP
#define PHANTOMPY_WEBELEMENT_HPP

#include <QtCore>
#include <QtWebKit>
#include <QtWebKitWidgets>

namespace ph {

class WebElement: public QObject {
    Q_OBJECT

public:
    WebElement(const QWebElement &element, QObject *parent=0);
    ~WebElement();

    bool isNull();

    QByteArray tagName();
    QByteArray toHtml();
    QByteArray toText();

    QByteArray evaluateJavaScript(const QString &data);
    QByteArray getClasses();
    QByteArray getAttributes();

    QWebElementCollection findAll(const QString &selector);

    bool hasClass(const QString &classname);

    bool hasAttribute(const QString &attrname);
    bool hasAttributes();

    void removeClass(const QString &classname);
    void removeAttribute(const QString &attrname);

    void setHtml(const QString &html);
    void setText(const QString &text);
private:
    QWebElement m_web_element;
};

}

#endif
