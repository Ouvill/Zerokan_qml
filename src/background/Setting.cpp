#include "Setting.h"
#include <QtCore/QSettings>
#include <QtWidgets/QInputDialog>
#include <QtDebug>

Setting::Setting(QObject *parent) : QObject(parent) {

}

Setting::~Setting() {

}

bool Setting::read() {
    QSettings settings(settingFile, QSettings::IniFormat, this);
    userName = settings.value("USER_NAME", "").toString();
    databaseName = settings.value("DATABASE_NAME", "zerokan.sqlite3").toString();

    while (userName.isEmpty()) {
        userName = QInputDialog::getText(0, tr("Input your account name"), tr("Input your account name"));
    }
    write();
    qDebug() << "userName" << userName;

    return true;
}

bool Setting::write() {
    QSettings settings(settingFile, QSettings::IniFormat, this);
    settings.setValue("USER_NAME", userName);
    settings.sync();
    return true;
}

QString Setting::getUserName() {
    return userName;
}
