#ifndef ZEROKAN_WT_FLIGHT_RECORDER_ACCESSSQL_H
#define ZEROKAN_WT_FLIGHT_RECORDER_ACCESSSQL_H


#include <QtCore/QObject>
#include <QtSql/QSqlDatabase>

class AccessSQL :public QObject {

    Q_OBJECT

public:
    explicit AccessSQL(QObject *parent = 0);
    ~AccessSQL();
    bool createConnection();
    bool makeTable();

public slots:


signals:

private:
    QSqlDatabase db;

};


#endif //ZEROKAN_WT_FLIGHT_RECORDER_ACCESSSQL_H
