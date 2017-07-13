#ifndef ZEROKAN_WT_FLIGHT_RECORDER_GAME_STATE_H
#define ZEROKAN_WT_FLIGHT_RECORDER_GAME_STATE_H
#include <string>
#include <QObject>


class GameState : public QObject {
    Q_OBJECT

public:
  enum {
    NotRunnningClient = -1,
    NotGaming = 0,
    GameStart = 1,
    GameRunning = 2,
    GameEnd = 3
  };

  GameState();
  ~GameState();
  int get();

public slots:

signals:
    void startGame();
    void endGame();
    void changeGameState(int state);

private:
    int state_;
    bool previous_valid;


};


#endif //ZEROKAN_WT_FLIGHT_RECORDER_GAME_STATE_H
