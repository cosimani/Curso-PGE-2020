#include <QApplication>
#include "visual.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Visual visual;
    visual.setTimer(50);
    visual.iniciarCamara();
    visual.show();

    return app.exec();
}
