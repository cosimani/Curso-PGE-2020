#include "principal.h"
#include "ui_principal.h"

Principal::Principal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Principal), camera(new QCamera(this))
{
    ui->setupUi(this);

   camerasList = QCameraInfo::availableCameras();
   for (int i=0 ; i<camerasList.size() ; i++)
       ui->cbSeleccionarCamara->addItem(camerasList.at(i).description());

   connect(ui->pbIniciarCamara, SIGNAL(clicked()), this, SLOT(slot_iniciarCamara()));
}

Principal::~Principal()
{
    delete ui;
}

void Principal::slot_iniciarCamara()
{
    QCameraInfo cameraInfo = camerasList.at(ui->cbSeleccionarCamara->currentIndex());

    delete camera;
    camera = new QCamera(cameraInfo, this);

    camera->setViewfinder(ui->visor);
    camera->start();
}
