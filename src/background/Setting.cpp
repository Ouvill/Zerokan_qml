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
    setUserName(settings.value("USER_NAME", "").toString());
    databaseName_ = settings.value("DATABASE_NAME", "zerokan.sqlite3").toString();

    while (userName_.isEmpty()) {
        setUserName(QInputDialog::getText(0, tr("Input your account name"), tr("Input your account name")));
    }
    write();
    qDebug() << "Setting::read";
    qDebug() << "userName_" << userName_;
    qDebug() << "databaseName_" << databaseName_;

    return true;
}

bool Setting::write() {
    QSettings settings(settingFile, QSettings::IniFormat, this);
    settings.setValue("USER_NAME", userName_);
    settings.sync();
    return true;
}


QString Setting::userName() {
    qDebug() << "userName() "<<userName_;
    return userName_;
}

bool Setting::set(QString userName, QString databaseName) {
    setUserName(userName);
    setDatadaseName(databaseName);
    return false;
}

QString Setting::databaseName() {
    return databaseName_;
}

void Setting::setUserName(QString userName ) {
    userName_ = userName;
    qDebug() << "send setUserNameSignal";
    emit changeUserName(userName_);
}

void Setting::setDatadaseName(QString databaseName) {
    databaseName_ = databaseName;
    emit changeDataBaseName(databaseName_);
}
