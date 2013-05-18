#ifndef PHANTOMPY_PAGE_HPP
#define PHANTOMPY_PAGE_HPP

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
    QString toHtml();

    bool isLoaded();
    bool hasLoadErrors();

private:
    bool loaded;
    bool error;

    QEventLoop m_event_loop;
    QWebPage m_page;

private slots:
    void loadFinished(bool ok);
};

#endif
