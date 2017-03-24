#ifndef UNTITLED_MAINWINDOW_H
#define UNTITLED_MAINWINDOW_H

#include <QMainWindow>
#include <QtCore/QThread>
#include "BackGround.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void background_loop();
    void background_stop();


private:
    Ui::MainWindow *ui;
    BackGround *background_;
    QThread *backgroundThread_;

};


#endif //UNTITLED_MAINWINDOW_H
