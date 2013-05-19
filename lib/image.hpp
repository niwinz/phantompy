#ifndef PHANTOMPY_IMAGE_HPP
#define PHANTOMPY_IMAGE_HPP

#include "page.hpp"

class Image: public QObject {
    Q_OBJECT

public:
    Image(Page *page, QObject *parent=0);
    ~Image();

    qint64 size();
    QByteArray format();
    qint32 quality();
    const char* data();

    void setQuality(const qint32 &format);
    void setFormat(const char *format);
    void setData(const QByteArray &data);

private:
    Page *p_page;

    QByteArray m_image;
    QByteArray m_format;
    qint32 m_quality;
};


#endif
