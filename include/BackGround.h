#ifndef ZEROKAN_WT_FLIGHT_RECORDER_BACKGROUND_H
#define ZEROKAN_WT_FLIGHT_RECORDER_BACKGROUND_H


#include <QtCore/QThread>
#include <QtCore/QTimerEvent>
#include "GameInfo.h"

class BackGround : public QObject {

    Q_OBJECT

public:
    BackGround(QObject *parent, GameInfo *gameInfo);

public slots:
    void loop();
    void stop();
    void check_exit();
    void startGameSlot();
    void endGameSlot();

signals:
    void killSignal(QString killMsg);
    void killedBySignal(QString killedMsg);
    void destroySignal(QString destroyMsg);

private:
    bool exit_flag = false;
    int myTimerId;
    int gamingTimerId;
    GameInfo *gameInfo_;
    Timer *timer_;

    void searchUserMsg();

protected:
    void timerEvent(QTimerEvent *e);
    User *user_;
    HudmsgReader *hudmsg_;


};


#endif //ZEROKAN_WT_FLIGHT_RECORDER_BACKGROUND_H
