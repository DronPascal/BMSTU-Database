#include <QCoreApplication>
#include <iostream>
#include <QtSql>
#include <QSqlDatabase>
#include <QDebug>
#include <windows.h>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("195.19.32.74");
    db.setDatabaseName("fn1131_2016");
    db.setUserName("student");
    db.setPassword("bmstu");
    db.setPort(5432);
    db.open();
    QSqlQuery query(";");
    query.exec("create table person "
              "(id integer primary key, "
              "firstname varchar(20), "
              "lastname varchar(30), "
              "age integer);");
    query.exec("insert into person "
              "(id, firstname, lastname, age)"
               "values (1,'Ivan', 'Ivanov', 19);");
    query.exec("SELECT * FROM person;");
    return a.exec();
}
