#include "frame.hpp"
#include "eventprocessor.hpp"
#include "timeout.hpp"
#include "context.hpp"

namespace ph {

Frame::Frame(QWebFrame *frame, QObject *parent): QObject(parent) {
    p_frame = frame;
    connect(p_frame->page(), &QWebPage::loadFinished, this, &Frame::loadFinished);
}

Frame::~Frame() {}


QByteArray Frame::captureImage(const char *format, int quality) {
    p_frame->page()->setViewportSize(p_frame->contentsSize());

    QImage image(p_frame->page()->viewportSize(), QImage::Format_ARGB32_Premultiplied);
    image.fill(Qt::transparent);

    QBuffer buffer;
    buffer.open(QIODevice::ReadWrite);

    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    p_frame->render(&painter);
    painter.end();

    image.save(&buffer, format, quality);
    return buffer.buffer();
}

QString Frame::toHtml() {
    return p_frame->toHtml();
}

QVariant Frame::evaluateJavaScript(const QString &js, bool expectLoad, int timeout) {
    QVariant result = p_frame->evaluateJavaScript(js);

    Timeout t(&m_loop, timeout);
    EventProcessor ep;

    t.start();
    ep.start();

    if (expectLoad) {
        m_loop.exec();
    }

    ep.stop();
    return result;
}

QWebElement Frame::findFirstElement(const QString &selector) {
    return p_frame->findFirstElement(selector);
}

QWebElementCollection Frame::findAll(const QString &selector) {
    return p_frame->findAllElements(selector);
}

QString Frame::getUrl() {
    return p_frame->url().toString();
}

void Frame::setUrl(const QString &url) {
    p_frame->setUrl(QUrl(url));
}

void Frame::load(const QString &url) {
    p_frame->load(QUrl(url));
}

void Frame::loadFinished(bool ok) {
    m_loop.quit();
}

}
