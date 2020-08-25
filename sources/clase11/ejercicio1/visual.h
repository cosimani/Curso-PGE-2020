#ifndef VISUAL_H
#define VISUAL_H

#include "ogl.h"
#include "capturador.h"

#include <QCamera>
#include <QCameraInfo>
#include <QList>

class Visual : public Ogl  {
    Q_OBJECT
public:
    Visual();
    void iniciarCamara();

protected:
    void initializeGL();
    void resizeGL(int ancho, int alto);
    void paintGL();

private:
    Capturador * capturador;
    QCamera * camera;

    void cargarTexturaCamara();

    unsigned char *texturaCamara;
    GLuint idTexturaCamara[1];

    void timeout();
};



#endif // VISUAL_H
