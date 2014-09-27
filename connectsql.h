#ifndef CONNECTSQL_H
#define CONNECTSQL_H
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlError>
#include<QSqlQuery>
#include<QDebug>
static bool sqlconnect(const QString &dbname)
{
    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection"))//in case connect to the QODBC many times
      db = QSqlDatabase::database("qt_sql_default_connection");
    else
      db = QSqlDatabase::addDatabase("QODBC");
    QString dsn ="DRIVER={SQL SERVER};SERVER=10.2.18.135;DATABASE=";
    db.setDatabaseName(dsn+dbname);
    db.setUserName("sa");
    db.setPassword("1226");
    if(!db.open())
       {
        qDebug()<< "error="<<db.lastError().text();
        return false;
       }
    return true;
}

#endif // CONNECTSQL_H
