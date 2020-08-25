#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QWidget>
#include <QCameraInfo>
#include <QCamera>

namespace Ui {
class Principal;
}

class Principal : public QWidget
{
    Q_OBJECT

public:
    explicit Principal(QWidget *parent = 0);
    ~Principal();

private:
    Ui::Principal *ui;
    QCamera *camera;
    QList<QCameraInfo> camerasList;

private slots:
    void slot_iniciarCamara();
};

#endif // PRINCIPAL_H
