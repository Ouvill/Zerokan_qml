#ifndef UNTITLED_MAINWINDOW_H
#define UNTITLED_MAINWINDOW_H

#include <QMainWindow>
#include <QtCore/QThread>
#include "GameInfo.h"
#include "BackGround.h"
#include <ui_mainwindow.h>


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow , private Ui::MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void startGameSlot();
    void endGameSlot();
    void killSlot(QString killMsg);
    void killedBySlot(QString killedMsg);
    void destroySlot(QString destroyMsg);
    void listWidgetClear();

signals:
    void background_loop();
    void background_stop();


private:
    Ui::MainWindow *ui;
    BackGround *background_;
    QThread *backgroundThread_;
    GameInfo *gameInfo_;

};


#endif //UNTITLED_MAINWINDOW_H
