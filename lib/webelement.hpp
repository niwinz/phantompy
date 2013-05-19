#ifndef PHANTOMPY_WEBELEMENT_HPP
#define PHANTOMPY_WEBELEMENT_HPP

#include <QtCore>
#include <QtWebKit>
#include <QtWebKitWidgets>

class WebElement: public QObject {
    Q_OBJECT

public:
    WebElement(const QWebElement &element, QObject *parent=0);
    ~WebElement();

    bool isNull();

    QByteArray tagName();
    QByteArray toHtml();
    QByteArray toText();

    QByteArray evaluateJavaScript(const QByteArray &data);
    QByteArray getClasses();
    QByteArray getAttributes();

    bool hasClass(const QByteArray &classname);

    bool hasAttribute(const QByteArray &attrname);
    bool hasAttributes();

    //void removeClass(const QByteArray &classname);
    //void removeAttribute(const QByteArray &attrname);

    //void setHtml(const QByteArray &html);
    //void setText(const QByteArray &text);
private:
    QWebElement m_web_element;
};

#endif
