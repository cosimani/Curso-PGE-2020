#ifndef VISOR_H
#define VISOR_H

#include <QCameraViewfinder>

class Visor : public QCameraViewfinder  {
    Q_OBJECT
public:
    explicit Visor(QWidget *parent = 0 ) : QCameraViewfinder(parent)  {   }
};

#endif // VISOR_H
