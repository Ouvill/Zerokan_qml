#include <include/Setting.h>
#include <QtDebug>
#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    setupUi(this);

    // setting;
    Setting *setting = new Setting();
    connect(setting, SIGNAL(changeUserName(QString)) , playerNameLabel,  SLOT(setText(QString)));
    setting->read();

    // gameInfo;
    gameInfo_ = new GameInfo(setting->userName());
    connect(gameInfo_->game_state_,SIGNAL(changeGameState(int)),
            this , SLOT(changeGameStateSlot(int)));


    // background
    background_ = new BackGround(0, gameInfo_);
    backgroundThread_ = new QThread(this);
    background_->moveToThread(backgroundThread_);
    connect(this, SIGNAL(background_loop()), background_, SLOT(loop()));
    connect(this, SIGNAL(background_stop()), background_, SLOT(stop()));
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

void MainWindow::changeGameStateSlot(int state) {
    switch (state) {
        case GameState::NotRunnningClient:
            clientStateLabel->setText(tr("not running"));
            gameStateLabel->setText(tr("not running"));
            break;

        case GameState::NotGaming:
            clientStateLabel->setText(tr("running"));
            gameStateLabel->setText(tr("not running"));
            break;

        case GameState::GameStart:
            clientStateLabel->setText(tr("running"));
            gameStateLabel->setText(tr("start"));
            break;

        case GameState::GameRunning:
            clientStateLabel->setText(tr("running"));
            gameStateLabel->setText(tr("running"));
            break;

        case GameState::GameEnd:
            clientStateLabel->setText(tr("running"));
            gameStateLabel->setText(tr("end"));
            break;
    }
}
