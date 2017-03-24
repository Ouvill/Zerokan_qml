#include <iostream>
#include <include/BackGround.h>
#include <QtWidgets/QApplication>
#include "src/gui/MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    return app.exec();

}