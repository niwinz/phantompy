#ifndef PHANTOMPY_PAGE_HPP
#define PHANTOMPY_PAGE_HPP

#include <memory>
#include <QtCore>
#include <QtWebKit>
#include <QtWebKitWidgets>


class Page: public QObject {
    Q_OBJECT

public:
    Page(QObject *parent=0);
    ~Page();

    void load(const QString &url);
    void setViewSize(int x, int y);

    QByteArray toHtml();
    QByteArray evaluateJavaScript(const QString &js);

    qint64 captureImage(char *format, int quality);
    const QByteArray& toImageBytes();

    bool isLoaded();
    bool hasLoadErrors();

private:
    bool loaded;
    bool error;

    QEventLoop m_event_loop;
    QWebPage m_page;
    QSize m_view_size;

    // Image
    QByteArray m_image_data;
    QString m_image_type;
    qint32  m_image_quality;

private slots:
    void loadFinished(bool ok);
};

#endif
