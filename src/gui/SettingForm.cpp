//
// Created by youhei on 2017/03/25.
//

#include "SettingForm.h"

SettingForm::SettingForm(QWidget *parent, Setting *setting) : QWidget(parent) , setting_(setting) {
    setupUi(this);
    connect(okButton, SIGNAL(clicked()), this, SLOT(okClicked()));
    connect(applyButton, SIGNAL(clicked()), this, SLOT(applyCliked()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
}

void SettingForm::okClicked() {
    applyCliked();
    close();
}

void SettingForm::applyCliked() {
    QString userName = userNameLineEdit->text();
    setting_->setUserName(userName);
}
