//
// Created by youhei on 2017/03/25.
//

#ifndef ZEROKAN_WT_FLIGHT_RECORDER_SETTINGFORM_H
#define ZEROKAN_WT_FLIGHT_RECORDER_SETTINGFORM_H


#include <QtCore/QObject>
#include <ui_SettingForm.h>
#include <include/Setting.h>

namespace Ui {
    class SettingForm;
}

class SettingForm : public QWidget , private Ui::SettingForm {
    Q_OBJECT


public:
    SettingForm(QWidget *parent, Setting *setting);


public slots:
    void okClicked();
    void applyCliked();

private:
    Setting *setting_;


};


#endif //ZEROKAN_WT_FLIGHT_RECORDER_SETTINGFORM_H
