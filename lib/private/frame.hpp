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

    //PDF output options
    void setPaperSize(const QVariantMap &size);
    QVariantMap paperSize() const;

    QByteArray captureImage(const char *format, int quality);
    bool renderPdf(const QString &filename);
    QString toHtml();
    QVariant evaluateJavaScript(const QString &data, bool expectLoad, int timeout);

    QWebElement findFirstElement(const QString &selector);
    QWebElementCollection findAll(const QString &selector);

    QString getUrl();
    void setUrl(const QString &url);
    void load(const QString &url);

private:
    QWebFrame *p_frame;
    QVariantMap m_paperSize; // For PDF output
    QEventLoop m_loop;

private slots:
    void loadFinished(bool ok);
};

}

#endif
