#ifndef ZEROKAN_WT_FLIGHT_RECORDER_SETTING_H
#define ZEROKAN_WT_FLIGHT_RECORDER_SETTING_H


#include <QtCore/QObject>

class Setting : public QObject {
    Q_OBJECT

public:
    Setting(QObject *parent = 0);
    ~Setting();
    QString userName();
    QString databaseName();

public slots:
    bool read();
    bool set(QString userName, QString databaseName);
    void setUserName(QString userName);
    void setDatadaseName(QString databaseName);
    bool write();

signals:
    void changeUserName(QString userName);
    void changeDataBaseName(QString);

private:
    const QString settingFile = "settings.ini";
    QString userName_;
    QString databaseName_;


};


#endif //ZEROKAN_WT_FLIGHT_RECORDER_SETTING_H
