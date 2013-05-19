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
    std::shared_ptr<QBuffer> toImageBytes(char *format, int quality);

    bool isLoaded();
    bool hasLoadErrors();

private:
    bool loaded;
    bool error;

    QEventLoop m_event_loop;
    QWebPage m_page;
    QSize m_view_size;

private slots:
    void loadFinished(bool ok);
};

#endif
