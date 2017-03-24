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

private:
    bool exit_flag = false;
    int myTimerId;
    GameInfo *gameInfo_;

protected:
    void timerEvent(QTimerEvent *e);

};


#endif //ZEROKAN_WT_FLIGHT_RECORDER_BACKGROUND_H
