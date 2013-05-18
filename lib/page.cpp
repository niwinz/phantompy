#include "page.hpp"

Page::Page(QObject *parent):QObject(parent) {
    this->m_page.mainFrame()->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);
    this->m_page.mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
    this->connect(this->m_page.mainFrame(), SIGNAL(loadFinished(bool)), this, SLOT(loadFinished(bool)));

    this->loaded = false;
    this->error = false;
}

Page::~Page() {}

void Page::load(const QString &_url) {
    QUrl url = QUrl::fromUserInput(_url);

    this->m_page.mainFrame()->load(url);
    this->m_event_loop.exec();
}

void Page::setViewSize(int x, int y) {
    this->m_page.setViewportSize(QSize(x, y));
}

QString Page::toHtml() {
    return this->m_page.mainFrame()->toHtml();
}

void Page::loadFinished(bool ok) {
    this->m_event_loop.quit();
    this->error = ok;
}

bool Page::isLoaded() {
    return this->loaded;
}

bool Page::hasLoadErrors() {
    return this->error;
}
