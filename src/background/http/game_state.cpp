#include "game_state.h"
#include "async_client.h"
#include <boost/asio.hpp>
#include <include/picojson.hpp>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtDebug>
#include <QtCore/QJsonArray>

GameState::GameState() : previous_valid(false) {
    state_=0;

}

GameState::~GameState() {
}

int GameState::get() {
    std::string data;

    boost::asio::io_service io_service;
    AsyncClient client(io_service, "localhost" , "8111", "/map_obj.json");
    io_service.run();

    if (!(client.is_complete())) {
        state_ = NotRunnningClient;
        emit changeGameState(state_);
        return state_;
    };

    data = client.body();
    QJsonDocument jsonDoc(QJsonDocument::fromJson(data.c_str()));

    bool current_valid;
    QJsonArray array = jsonDoc.array();
    if (array.size() != 1) {
        current_valid = true;
    } else {
        current_valid = false;
    }

    if ( current_valid == true && previous_valid == false ) {
        state_ = GameRunning;
        qDebug() << "send startGameSignal";
        emit startGame();
    }

    if ( current_valid == false && previous_valid == true ) {
        state_ = NotGaming;
        qDebug() << "send endGameSignal";
        emit endGame();
    }


//  if (previous_map_obj == "" && current_map_obj_json == "") {
//    state_ = NotGaming;
//  } else if (previous_map_obj == "" && current_map_obj_json != "") {
//    state_ = GameStart;
//  } else if (previous_map_obj != "" && current_map_obj_json != "") {
//    state_ = GameRunning;
//  } else if (previous_map_obj != "" && current_map_obj_json == "") {
//    state_ = GameEnd;
//  }

    emit changeGameState(state_);
    previous_valid = current_valid;
    return state_;
}
