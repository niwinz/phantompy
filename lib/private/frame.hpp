#ifndef PHANTOMPY_FRAME_HPP
#define PHANTOMPY_FRAME_HPP

#include <QtCore>
#include <QtWebKit>
#include <QtWebKitWidgets>

namespace ph {

class Frame: public QObject {
    Q_OBJECT

public:
    Frame(QWebFrame *frame, QObject *parent=0);
    ~Frame();

    QByteArray captureImage(const char *format, int quality);
    QString toHtml();
    QVariant evaluateJavaScript(const QString &data, bool expectLoad, int timeout);

    QWebElement findFirstElement(const QString &selector);
    QWebElementCollection findAll(const QString &selector);

    QString getUrl();
    void setUrl(const QString &url);
    void load(const QString &url);

private:
    QWebFrame *p_frame;
    QEventLoop m_loop;

private slots:
    void loadFinished(bool ok);
};

}

#endif
