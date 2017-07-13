//
// Created by youhei on 2017/03/24.
//

#include "GameInfo.h"

GameInfo::GameInfo(QString userName){
    user_ = new User(userName.toStdString());
    game_state_ = new GameState();
    hudmsg_ = new HudmsgReader();
    damages_ = new Damages();
}
