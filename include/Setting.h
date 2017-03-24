#ifndef ZEROKAN_WT_FLIGHT_RECORDER_SETTING_H
#define ZEROKAN_WT_FLIGHT_RECORDER_SETTING_H


#include <QtCore/QObject>

class Setting : public QObject {
    Q_OBJECT

public:
    Setting(QObject *parent = 0);
    ~Setting();
    QString getUserName();

public slots:
    bool read();
    bool write();

private:
    const QString settingFile = "settings.ini";
    QString userName;
    QString databaseName;
};


#endif //ZEROKAN_WT_FLIGHT_RECORDER_SETTING_H
