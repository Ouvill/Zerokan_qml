#ifndef ZEROKAN_WT_FLIGHT_RECORDER_BACKGROUND_H
#define ZEROKAN_WT_FLIGHT_RECORDER_BACKGROUND_H


#include <QtCore/QThread>
#include <QtCore/QTimerEvent>

class BackGround : public QObject {

    Q_OBJECT

public:
    BackGround(QObject *parent = 0);

public slots:
    void loop();
    void stop();
    void check_exit();

private:
    bool exit_flag = false;
    int myTimerId;


protected:
    void timerEvent(QTimerEvent *e);

};


#endif //ZEROKAN_WT_FLIGHT_RECORDER_BACKGROUND_H
