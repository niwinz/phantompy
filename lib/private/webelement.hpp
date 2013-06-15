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

    QString tagName();
    QString toHtml();
    QString toText();

    QVariant evaluateJavaScript(const QString &js, bool expectLoad, int timeout);

    QStringList getClasses();
    QStringList getAttributeNames();
    QString getAttribute(const QString &attrname);

    QWebElementCollection findAll(const QString &selector);

    bool hasClass(const QString &classname);
    void addClass(const QString &classname);
    void removeClass(const QString &classname);

    void append(const QString &html);
    void append(WebElement *element);

    void appendAfter(const QString &html);
    void appendAfter(WebElement *element);

    void setAttribute(const QString &attrname, const QVariant &value);
    void removeAttribute(const QString &attrname);

    bool hasAttribute(const QString &attrname);
    bool hasAttributes();

    void replace(const QString &html);
    void replace(WebElement *element);

    void removeAllChildren();
    void removeFromDocument();
    QWebElement takeFromDocument();

    void wrap(const QString &html);
    void wrap(WebElement *element);

    QWebElement next();
    QWebElement prev();

    void setHtml(const QString &html);
    void setText(const QString &text);

private:
    QWebElement m_web_element;
    QWebElement internalElement();

    QEventLoop m_loop;

private slots:
    void loadFinished(bool ok);
};

}

#endif
