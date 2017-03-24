#include <QtSql>
#include <QtWidgets/QMessageBox>
#include "AccessSQL.h"
#include <QtDebug>


AccessSQL::~AccessSQL() {
    db.close();
}


AccessSQL::AccessSQL(QObject *parent) : QObject(parent) {
    qDebug("make AccessSQL");
    createConnection();
    makeTable();
}

bool AccessSQL::createConnection() {
    qDebug() << "make sqlite database";
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./testdatabase.sqlite3");
    if (!db.open()) {
        QMessageBox::critical(0, QObject::tr("Database Error"), db.lastError().text());
        return false;
    }
    qDebug() << "tables 1";
    for (int i = 0; i < db.tables().count(); i ++) {
        qDebug() << db.tables().at(i);
    }
    return true;
}

bool AccessSQL::makeTable() {
    QSqlQuery query(db);
    query.exec("create table test1(id, name, memo");
    qDebug() << "tables 2";
    for (int i = 0; i < db.tables().count(); i ++) {
        qDebug() << db.tables().at(i);
    }

    // データを書き込む
    query.prepare("insert into test1 (id, name, memo) "
                          "values (?, ?, ?)");
    for (int i = 0; i < 20; i ++) {
        query.bindValue(0, i);
        query.bindValue(1, QString("name%1").arg(i));
        query.bindValue(2, QString("memo%1").arg(i));
        query.exec();
    }

    // データを出力する
    qDebug() << "records";
    query.exec("select * from test1");
    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString memo = query.value(2).toString();
        qDebug() << QString("id(%1),name(%2),memo(%3)").arg(id).arg(name).arg(memo);
    }

    return false;
}




