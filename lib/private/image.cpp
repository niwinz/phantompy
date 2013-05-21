#include "image.hpp"

namespace ph {

Image::Image(Frame *frame, QObject *parent): QObject(parent) {
    p_frame = frame;
}

Image::~Image() {}


void Image::setFormat(const char *format) {
    m_format = QByteArray(format);
}

void Image::setQuality(const qint32 &quality) {
    m_quality = quality;
}

void Image::setData(const QByteArray &data) {
    m_image = data;
}

const char* Image::data() {
    return m_image.constData();
}

qint64 Image::size() {
    return m_image.size();
}

QByteArray Image::format() {
    return m_format;
}

qint32 Image::quality() {
    return m_quality;
}

}
