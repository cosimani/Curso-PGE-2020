#include "visual.h"
#include <GL/glu.h>
#include <QKeyEvent>

Visual::Visual() : Ogl()  {

}

void Visual::iniciarCamara()  {
    capturador = new Capturador;

    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();

    if ( ! cameras.isEmpty() )  {
        camera = new QCamera(cameras.at(0));
        camera->setViewfinder(capturador);
        camera->start();
    }
    glGenTextures(1, idTexturaCamara);
}

void Visual::cargarTexturaCamara()  {

    QVideoFrame frameActual = capturador->getFrameActual();
    texturaCamara = frameActual.bits();

    glBindTexture(GL_TEXTURE_2D, idTexturaCamara[0]);  // Activamos idTextura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // GL_LINEAR - Interpolación
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // GL_NEAREST - Sin

    glTexImage2D(GL_TEXTURE_2D, 0, 3, frameActual.width(), frameActual.height(), 0, GL_BGRA, GL_UNSIGNED_BYTE, texturaCamara);
}

void Visual::initializeGL()  {
    glEnable(GL_TEXTURE_2D);
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
}

void Visual::resizeGL(int ancho, int alto)  {
    glViewport( 0, 0, (GLint)ancho, (GLint)alto );
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//    gluPerspective(45.0f, (GLfloat)ancho/(GLfloat)alto, 1, 100.0f);
    glOrtho(-2, 2, -2, 2, -10, 10);
    glMatrixMode(GL_MODELVIEW);
}

void Visual::paintGL()  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glBegin(GL_QUADS);
        glTexCoord2f(0, 0);  glVertex3f(-1, -1, -5);
        glTexCoord2f(1, 0);  glVertex3f(1, -1, -5);
        glTexCoord2f(1, 1);  glVertex3f(1, 1, -5);
        glTexCoord2f(0, 1);  glVertex3f(-1, 1, -5);
    glEnd();

    glFlush();
}

void Visual::timeout()  {
    this->cargarTexturaCamara();
    this->updateGL();
}

