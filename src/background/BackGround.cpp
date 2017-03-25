#include <iostream>
#include <include/AccessSQL.h>
#include <QtDebug>
#include <QtCore/QThread>
#include <boost/filesystem/operations.hpp>
#include "BackGround.h"

static const int LOOP_TIME = 1000;
static const std::string RECORDS_FILE = "./data/records.csv";
static const std::string REVANGE_LIST = "./data/revange_list.csv";

struct thread_aborted{};

BackGround::BackGround(QObject *parent, GameInfo *gameInfo) : QObject(parent) , gameInfo_(gameInfo){
    connect(gameInfo_->game_state_, SIGNAL(startGame()),
            this, SLOT(startGameSlot()));
    connect(gameInfo_->game_state_, SIGNAL(endGame()),
    this, SLOT(endGameSlot()));

    user_ = gameInfo->user_;
    hudmsg_ = gameInfo->hudmsg_;

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
    // 常時
    if (e->timerId() == myTimerId) {
        try {
            gameInfo_->game_state_->get();

            qDebug() << "loop";
            check_exit();
        } catch (thread_aborted& e) {

        }
    }

    // 試合中だけ
    if ( e->timerId() == gamingTimerId) {
        searchUserMsg();

    }

}

void BackGround::searchUserMsg() {

    Damages *tmp_damages = new Damages;
    hudmsg_->get_damages(*tmp_damages);

    qDebug() << "searchUserMsg";
    for (auto itr = tmp_damages->begin(); itr != tmp_damages->end(); ++itr) {

        switch (itr->msg().type()) {
            case Msg::SHOTDOWN_MSG : {
                ShotDownMsg shotDownMsg(itr->msg());
                // kill
                if (shotDownMsg.killer().find(user_->name()) != std::string::npos) {
                    std::string killMsg = shotDownMsg.victim() + "(" + shotDownMsg.victim_airframe() + ")";
                    user_->record()->add_kill_count();
                    emit killSignal(killMsg.c_str());
                }

                // killed by
                if (shotDownMsg.victim().find(user_->name()) != std::string::npos) {
                    std::string killedByMsg = shotDownMsg.killer() + "(" + shotDownMsg.killer_airframe() + (")");
                    user_->record()->add_death_count();
                    emit killedBySignal(killedByMsg.c_str());

                    if (!boost::filesystem::exists(REVANGE_LIST)) {
                        std::ofstream of(REVANGE_LIST, std::ios::app);
                        of << "戦闘開始時刻,敵プレイヤー名,敵の機体,自身の機体" << std::endl;
                        of.close();
                    }

                    time_t time = timer_->start_time();
                    struct tm *tm_st = localtime(&time);
                    std::ofstream of(REVANGE_LIST, std::ios::app);
                    of << tm_st->tm_year << tm_st->tm_mon + 1 << tm_st->tm_mday << "_" << tm_st->tm_hour
                       << tm_st->tm_min << tm_st->tm_sec << ",";
                    of << shotDownMsg.killer() << ",";
                    of << shotDownMsg.killer_airframe() << ",";
                    of << shotDownMsg.victim_airframe() << std::endl;
                    of.close();

                }


                break;
            }

            case Msg::DESTROYED_MSG : {
                DestroyedMsg destroyedMsg(itr->msg());
                if (destroyedMsg.killer().find(user_->name()) != std::string::npos) {
                    user_->record()->add_destroy_count();
                    emit destroySignal(destroyedMsg.victim().c_str());

                }


                break;
            }

            case Msg::CRASHED_MSG : {
                DamageMsg crashedMsg(itr->msg());
                if (crashedMsg.killer().find(user_->name()) != std::string::npos) {
                    user_->record()->add_death_count();
                }

                break;
            }
        }
    }
}

void BackGround::startGameSlot() {
    user_->reset_record();
    timer_ = new Timer();
    qDebug() << "start gaming loop";
    gamingTimerId = startTimer(LOOP_TIME);

    //to trash
    Damages *tmp_damages = new Damages;
    hudmsg_->get_damages(*tmp_damages);
    delete tmp_damages;
}

void BackGround::endGameSlot() {
    timer_->stop();
    user_->record()->export_csv(RECORDS_FILE,timer_->start_time());
    killTimer(gamingTimerId);
}

