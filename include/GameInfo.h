//
// Created by youhei on 2017/03/24.
//

#ifndef ZEROKAN_WT_FLIGHT_RECORDER_GAMEINFO_H
#define ZEROKAN_WT_FLIGHT_RECORDER_GAMEINFO_H

#include <QtCore/QObject>
#include "game_state.h"
#include "user.h"
#include "hudmsg_reader.h"
#include "damages.h"

class GameInfo : public QObject {
    Q_OBJECT

public:
    User *user_;
    GameState *game_state_;
    Damages *damages_;
    HudmsgReader *hudmsg_;

    GameInfo(QString userName);

public slots:

signals:

private:

};


#endif //ZEROKAN_WT_FLIGHT_RECORDER_GAMEINFO_H
