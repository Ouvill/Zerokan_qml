#include <iostream>
#include <include/AccessSQL.h>
#include <QtDebug>
#include <QtCore/QThread>
#include "BackGround.h"

static const int LOOP_TIME = 5000;

struct thread_aborted{};

BackGround::BackGround(QObject *parent, GameInfo *gameInfo) : QObject(parent) , gameInfo_(gameInfo){

}

void BackGround::loop() {
    myTimerId = startTimer(LOOP_TIME);
}

void BackGround::check_exit() {
    if (exit_flag) {
        throw thread_aborted{};
    }

}

void BackGround::stop() {
    exit_flag = true;
}


void BackGround::timerEvent(QTimerEvent *e) {
    if (e->timerId() == myTimerId) {
        try {
            gameInfo_->game_state_->get();

            qDebug() << "loop";
            check_exit();
        } catch (thread_aborted& e) {

        }
    }
}
