#include "frame.hpp"

namespace ph {

Frame::Frame(QWebFrame *frame, QObject *parent): QObject(parent) {
    p_frame = frame;
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

QString Frame::evaluateJavaScript(const QString &js) {
    QVariant result = p_frame->evaluateJavaScript(js);
    return result.toString();
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

}
