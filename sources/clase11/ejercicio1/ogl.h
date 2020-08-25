#ifndef OGL_H
#define OGL_H

#include <QGLWidget>
#include <QTimer>
#include <QKeyEvent>

class Ogl : public QGLWidget  {
    Q_OBJECT

public:
    Ogl()  {  }

    void setTimer(int timerIntervalo)  {
        if(timerIntervalo > 0)  {
            timerIntervalo = qMin(15, timerIntervalo);
            connect(&timer, SIGNAL(timeout()), this, SLOT(slot_timeout()));
            timer.start(timerIntervalo);
        }
    }

protected:
    virtual void initializeGL() = 0;
    virtual void resizeGL(int width, int height) = 0;
    virtual void paintGL() = 0;

    virtual void keyPressEvent(QKeyEvent *e)  {
        switch( e->key() )  {
            case Qt::Key_Escape:
                close();
        }
    }

    virtual void timeout()  {
        this->updateGL();
    }

protected slots:
    virtual void slot_timeout()  {
        this->timeout();
    }

private:
    QTimer timer;
};

#endif // OGL_H
