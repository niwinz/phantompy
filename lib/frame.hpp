#ifndef PHANTOMPY_FRAME_HPP
#define PHANTOMPY_FRAME_HPP

#include <QtCore>
#include <QtWebKit>
#include <QtWebKitWidgets>

class Page;

class Frame: public QObject {
    Q_OBJECT

public:
    Frame(QWebFrame *frame, QObject *parent=0);
    ~Frame();

    QByteArray captureImage(const char *format, int quality);
    QByteArray toHtml();
    QByteArray evaluateJavaScript(const QString &data);

    QWebElement findFirstElement(const QString &selector);

private:
    QWebFrame *p_frame;
};

#endif
