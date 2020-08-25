#ifndef VIDEOWIDGETSURFACE_H
#define VIDEOWIDGETSURFACE_H

#include <QtMultimedia/QAbstractVideoSurface>
#include <QtMultimedia/QVideoFrame>

class Capturador : public QAbstractVideoSurface  {
    Q_OBJECT

public:
    Capturador(QObject *parent = 0) : QAbstractVideoSurface(parent)  {  }

    QList<QVideoFrame::PixelFormat> supportedPixelFormats(
            QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const  {
        if (handleType == QAbstractVideoBuffer::NoHandle) {
            return QList<QVideoFrame::PixelFormat>()
                    << QVideoFrame::Format_RGB32
                    << QVideoFrame::Format_ARGB32;
        } else {
            return QList<QVideoFrame::PixelFormat>();
        }
    }

    bool present(const QVideoFrame &frame)  {
        frameActual = frame;

        frameActual.map(QAbstractVideoBuffer::ReadOnly);

        return true;  // Para devolver true si este frame fue usado
    }

    QVideoFrame getFrameActual()  {  return frameActual;  }

private:
    QVideoFrame frameActual;
};

#endif
