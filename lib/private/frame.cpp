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

void Frame::setPaperSize(const QVariantMap &size) {
    m_paperSize = size;
}

QVariantMap Frame::paperSize() const {
    return m_paperSize;
}


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

#define PDF_DPI 72            // Different defaults. OSX: 72, X11: 75(?), Windows: 96

//This function is reused from https://github.com/ariya/phantomjs/blob/master/src/webpage.cpp#L1033
qreal stringToPointSize(const QString &string) {
    static const struct {
        QString unit;
        qreal factor;
    } units[] = {
        { "mm", 72 / 25.4 },
        { "cm", 72 / 2.54 },
        { "in", 72 },
        { "px", 72.0 / PDF_DPI / 2.54 },
        { "", 72.0 / PDF_DPI / 2.54 }
    };
    for (uint i = 0; i < sizeof(units) / sizeof(units[0]); ++i) {
        if (string.endsWith(units[i].unit)) {
            QString value = string;
            value.chop(units[i].unit.length());
            return value.toDouble() * units[i].factor;
        }
    }
    return 0;
}

//This function is reused from https://github.com/ariya/phantomjs/blob/master/src/webpage.cpp#L1055
qreal printMargin(const QVariantMap &map, const QString &key) {
    const QVariant margin = map.value(key);
    if (margin.isValid() && margin.canConvert(QVariant::String)) {
        return stringToPointSize(margin.toString());
    } else {
        return 0;
    }
}

//This function is reused mostly from https://github.com/ariya/phantomjs/blob/master/src/webpage.cpp#L1065
bool Frame::renderPdf(const QString &fileName) {
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    printer.setResolution(PDF_DPI);
    QVariantMap paperSize = m_paperSize;

    if (paperSize.isEmpty()) {
        const QSize pageSize = p_frame->contentsSize();
        paperSize.insert("width", QString::number(pageSize.width()) + "px");
        paperSize.insert("height", QString::number(pageSize.height()) + "px");
        paperSize.insert("margin", "0px");
    }

    if (paperSize.contains("width") && paperSize.contains("height")) {
        const QSizeF sizePt(ceil(stringToPointSize(paperSize.value("width").toString())),
                            ceil(stringToPointSize(paperSize.value("height").toString())));
        printer.setPaperSize(sizePt, QPrinter::Point);
    } else if (paperSize.contains("format")) {
        const QPrinter::Orientation orientation = paperSize.contains("orientation")
                && paperSize.value("orientation").toString().compare("landscape", Qt::CaseInsensitive) == 0 ?
                    QPrinter::Landscape : QPrinter::Portrait;
        printer.setOrientation(orientation);
        static const struct {
            QString format;
            QPrinter::PaperSize paperSize;
        } formats[] = {
            { "A0", QPrinter::A0 },
            { "A1", QPrinter::A1 },
            { "A2", QPrinter::A2 },
            { "A3", QPrinter::A3 },
            { "A4", QPrinter::A4 },
            { "A5", QPrinter::A5 },
            { "A6", QPrinter::A6 },
            { "A7", QPrinter::A7 },
            { "A8", QPrinter::A8 },
            { "A9", QPrinter::A9 },
            { "B0", QPrinter::B0 },
            { "B1", QPrinter::B1 },
            { "B2", QPrinter::B2 },
            { "B3", QPrinter::B3 },
            { "B4", QPrinter::B4 },
            { "B5", QPrinter::B5 },
            { "B6", QPrinter::B6 },
            { "B7", QPrinter::B7 },
            { "B8", QPrinter::B8 },
            { "B9", QPrinter::B9 },
            { "B10", QPrinter::B10 },
            { "C5E", QPrinter::C5E },
            { "Comm10E", QPrinter::Comm10E },
            { "DLE", QPrinter::DLE },
            { "Executive", QPrinter::Executive },
            { "Folio", QPrinter::Folio },
            { "Ledger", QPrinter::Ledger },
            { "Legal", QPrinter::Legal },
            { "Letter", QPrinter::Letter },
            { "Tabloid", QPrinter::Tabloid }
        };
        printer.setPaperSize(QPrinter::Letter); // Fallback
        for (uint i = 0; i < sizeof(formats) / sizeof(formats[0]); ++i) {
            if (paperSize.value("format").toString().compare(formats[i].format, Qt::CaseInsensitive) == 0) {
                printer.setPaperSize(formats[i].paperSize);
                break;
            }
        }
    } else {
        return false;
    }
    if (paperSize.contains("border") && !paperSize.contains("margin")) {
        // backwards compatibility
        paperSize["margin"] = paperSize["border"];
    }

    qreal marginLeft = 0;
    qreal marginTop = 0;
    qreal marginRight = 0;
    qreal marginBottom = 0;

    if (paperSize.contains("margin")) {
        const QVariant margins = paperSize["margin"];
        if (margins.canConvert(QVariant::Map)) {
            const QVariantMap map = margins.toMap();
            marginLeft = printMargin(map, "left");
            marginTop = printMargin(map, "top");
            marginRight = printMargin(map, "right");
            marginBottom = printMargin(map, "bottom");
        } else if (margins.canConvert(QVariant::String)) {
            const qreal margin = stringToPointSize(margins.toString());
            marginLeft = margin;
            marginTop = margin;
            marginRight = margin;
            marginBottom = margin;
        }
    }

    printer.setPageMargins(marginLeft, marginTop, marginRight, marginBottom, QPrinter::Point);

    p_frame->print(&printer);
    return true;
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
    QNetworkRequest request = QNetworkRequest(url);
    Context::instance()->applyHTTPHeaders(request);
    p_frame->load(request);
}

void Frame::loadFinished(bool ok) {
    m_loop.quit();
}

}
