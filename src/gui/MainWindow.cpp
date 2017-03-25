#include <include/Setting.h>
#include <QtDebug>
#include "MainWindow.h"
#include "SettingForm.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    setupUi(this);

    // setting;
    setting_ = new Setting();
    connect(setting_, SIGNAL(changeUserName(QString)) , playerNameLabel,  SLOT(setText(QString)));
    setting_->read();

    // gameInfo;
    gameInfo_ = new GameInfo(setting_->userName());
    connect(gameInfo_->game_state_,SIGNAL(startGame()),
            this , SLOT(startGameSlot()));
    connect(gameInfo_->game_state_,SIGNAL(endGame()),
            this , SLOT(endGameSlot()));

    // background
    background_ = new BackGround(0, gameInfo_);
    backgroundThread_ = new QThread();
    background_->moveToThread(backgroundThread_);
    connect(this, SIGNAL(background_loop()), background_, SLOT(loop()));
    connect(this, SIGNAL(background_stop()), background_, SLOT(stop()));
    connect(backgroundThread_, SIGNAL(finished()), background_, SLOT(deleteLater()));

    connect(background_, SIGNAL(killSignal(QString)),
            this , SLOT(killSlot(QString)));
    connect(background_, SIGNAL(killedBySignal(QString)),
            this , SLOT(killedBySlot(QString)));
    connect(background_, SIGNAL(destroySignal(QString)),
            this , SLOT(destroySlot(QString)));
    backgroundThread_->start();
    background_loop();

    //menu
    connect(settingAction, SIGNAL(triggered()) , this , SLOT(settingSelected()));
}

MainWindow::~MainWindow()
{
    delete ui;
    background_stop();
    backgroundThread_->exit();
}

void MainWindow::startGameSlot() {
    listWidgetClear();
    clientStateLabel->setText(tr("running"));
    gameStateLabel->setText(tr("start"));
    QThread::sleep(3);
    gameStateLabel->setText(tr("running"));
}

void MainWindow::endGameSlot() {
    clientStateLabel->setText(tr("running"));
    gameStateLabel->setText(tr("end"));
    QThread::sleep(3);
    gameStateLabel->setText(tr("not running"));

}

void MainWindow::killSlot(QString killMsg) {
    killListWidget->addItem(killMsg);
}

void MainWindow::killedBySlot(QString killedMsg) {
    killedByListWidget->addItem(killedMsg);
}

void MainWindow::destroySlot(QString destroyMsg) {
    destroyListWidget->addItem(destroyMsg);
}

void MainWindow::listWidgetClear() {
    killListWidget->clear();
    killedByListWidget->clear();
    destroyListWidget->clear();
}

void MainWindow::settingSelected() {
    settingForm_ = new SettingForm(0,setting_);
    settingForm_->show();

}

