#include <include/Setting.h>
#include "MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // readSetting
    Setting setting;
    setting.read();

    // background
    background_ = new BackGround(this);
    backgroundThread_ = new QThread(this);
    background_->moveToThread(backgroundThread_);
//    connect(this, SIGNAL(background_stop()), background_, SLOT(stop()));
    connect(backgroundThread_, SIGNAL(finished()), background_, SLOT(deleteLater()));
    backgroundThread_->start();
    background_loop();


}

MainWindow::~MainWindow()
{
    delete ui;
    background_stop();
    backgroundThread_->exit();
}
