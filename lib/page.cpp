#include "page.hpp"

Page::Page(QObject *parent):QObject(parent) {
    connect(&m_page, SIGNAL(loadFinished(bool)), this, SLOT(loadFinished(bool)));

    loaded = false;
    error = false;
}

Page::~Page() {}

void Page::load(const QString &_url) {
    QUrl url = QUrl::fromUserInput(_url);

    m_page.mainFrame()->load(url);
    m_page.mainFrame()->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);
    m_page.mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
    m_page.setViewportSize(m_view_size);

    m_event_loop.exec();
}

void Page::setViewSize(int x, int y) {
    this->m_view_size = QSize(x, y);
}

void Page::loadFinished(bool ok) {
    m_event_loop.quit();
    error = ok;
}

bool Page::isLoaded() {
    return loaded;
}

bool Page::hasLoadErrors() {
    return error;
}

QByteArray Page::toHtml() {
    return m_page.mainFrame()->toHtml().toUtf8();
}

qint64 Page::captureImage(char *format, int quality) {
    m_image_type = QString::fromUtf8(format);
    m_image_quality = quality;

    m_page.setViewportSize(m_page.mainFrame()->contentsSize());

    QImage image(m_page.viewportSize(), QImage::Format_ARGB32_Premultiplied);
    image.fill(Qt::transparent);

    if (image.isNull()) {
        qDebug() << "IMAGE IS NULL";
        return -1;
    }

    QBuffer buffer(&m_image_data);
    buffer.open(QIODevice::ReadWrite);

    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    m_page.mainFrame()->render(&painter);
    painter.end();

    image.save(&buffer, "PNG");
    return buffer.size();
}

const QByteArray& Page::toImageBytes() {
    return m_image_data;
}

QByteArray Page::evaluateJavaScript(const QString &js) {
    QVariant result = m_page.mainFrame()->evaluateJavaScript(js);
    return result.toString().toUtf8();
}
