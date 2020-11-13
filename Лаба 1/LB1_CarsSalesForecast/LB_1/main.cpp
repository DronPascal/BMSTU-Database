#include <QCoreApplication>
#include <iostream>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include  <QSqlError>
#include <QVariant>
#include <QSqlRecord>
#include <QDebug>
#include <iomanip>
#include <string>
#include "stdlib.h"

int main(int argc, char *argv[])
{
    setlocale(0, "russian");
    QCoreApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("PasShiDB");
    if (!db.open())
    {
        std::cout << "DB is not opened" << std::endl;
        return a.exec();
    }
    QSqlQuery myQ(db);

    myQ.exec("PRAGMA foreign_keys = ON");

    myQ.exec("DROP TABLE FN11_31b");
    myQ.exec("CREATE TABLE FN11_31b ("
             "num int, "
             "name varchar[12] PRIMARY KEY, "
             "age int"
             ");");
    myQ.exec("DROP TABLE FN11_32b");
    myQ.exec("CREATE TABLE FN11_32b ("
             "num int , "
             "name varchar[12] PRIMARY KEY, "
             "age int"
             ");");
    myQ.exec("DROP TABLE FN11_33b");
    myQ.exec("CREATE TABLE FN11_33b ("
             "num int , "
             "name varchar[12] PRIMARY KEY, "
             "age int"
             ");");

    myQ.exec("CREATE TABLE car_manufacturers ("
             "model varchar[20] PRIMARY KEY,"
             "manufacturer [15],"
             "country varchar[15] PRIMARY KEY);");


    myQ.exec("DROP TABLE FN11");
    myQ.exec("CREATE TABLE FN11 ("
             "FN11-31b varchar[12] REFERENCES FN11_31b(name), "
             "FN11-32b varchar[12] REFERENCES FN11_32b(name), "
             "FN11-33b varchar[12] REFERENCES FN11_33b(name)"
             ");");

    myQ.exec("INSERT INTO FN11_31b(num, name, age) "
    "VALUES (1, 'Sashko', 54), (2, 'Dron', 311), (3, 'Vano', 4975);");
    myQ.exec("INSERT INTO FN11_32b(num, name, age) "
    "VALUES (1, 'Lily', 61), (2, 'Danya', 3351), (3, 'Ilya', 4134),(4, 'Vasya', 641), (5, 'Olesya', 1145);");
    myQ.exec("INSERT INTO FN11_33b(num, name, age) "
    "VALUES (1, 'Petya', 0), (2, 'Dasha', 3), (3, 'Kuzya', 45),(4, 'Dima', 11),(5, 'Alan', 31),(6, 'Valya', 731),(7, 'Lev', 151)");

   //SELECT * FROM FN11_32b

    myQ.exec("DROP TABLE car_manufacturers");
    myQ.exec("DROP TABLE sales_forecast");
    myQ.exec("DROP TABLE sanctions");

    myQ.exec("CREATE TABLE car_manufacturers ("
             "model VARCHAR(20) NOT NULL,"
             "manufacturer VARCHAR(15) NOT NULL,"
             "country VARCHAR(15) NOT NULL,"
             "PRIMARY KEY (manufacturer),"
             "PRIMARY KEY (country)");

    myQ.exec("CREATE TABLE sales_forecast ("
             "model VARCHAR(20) NOT NULL,"
             "year SMALLINT UNSUGNED NOT NULL,"
             "price numeric(15, 2) NOT NULL,"
             "FOREIGN KEY (model) REFERENCES car_manufacturers(model)");

    myQ.exec("CREATE TABLE sanctions ("
             "country VARCHAR(20) NOT NULL,"
             "starting_year SMALLINT UNSUGNED NOT NULL,"
             "FOREIGN KEY (country) REFERENCES car_manufacturers(country)");

    myQ.exec("INSERT INTO car_manufacturers(model, manufacturer, country)"
             "VALUES ('Tesla Model 3','Tesla','USA'),"
             "('Tesla Model S','Tesla','USA'),"
             "('Tesla Model X','Tesla','USA'),"
             "('Mitsubishi L200','Mitsubishi','Japan'),"
             "('Mitsubishi Pajero Sport','Mitsubishi','Japan'),"
             "('Nissan GT-R','Nissan','Japan'),"
             "('Nissan Juke','Nissan','Japan'),"
             "('Nissan X-Trail','Nissan','Japan'),"
             "('Audi A5','Audi','Germany'),"
             "('Audi Q8','Mitsubishi','Germany')");

     myQ.exec("INSERT INTO sales_forecast(model, year, price)"
              "VALUES ('Tesla Model 3', 2017, 45000000000),"
              "('Tesla Model S', 2016, 30000000000),"
              "('Tesla Model X', 2015, 25000000000),"
              "('Tesla Model X', 2016, 15000000000),"
              "('Mitsubishi L200', 2019, 10000000000),"
              "('Mitsubishi Pajero Sport', 2015, 16000000000),"
              "('Nissan GT-R', 2016, 23000000000),"
              "('Nissan GT-R', 2018, 9000000000),"
              "('Nissan Juke', 2018, 16000000000),"
              "('Nissan X-Trail', 2018, 11000000000),"
              "('Audi A5', 2016, 24000000000),"
              "('Audi A5', 2017, 17000000000),"
              "('Audi Q8', 2018, 20000000000)");

     myQ.exec("INSERT INTO sanctions(country, starting_year)"
              "VALUES ('USA', 2016)"
              "('Japan', 2017)"
              "('Germany', 2018)");


    std::string command="e";

    while (command != "exit")
    {
        std::cout << "Enter command: ";
        std::getline(std::cin, command);
        std::cout << "Your command is: " << command << std::endl;
        myQ.exec(command.c_str());

        if (myQ.isSelect())
        {
            std::cout << "TABLE Selected\n";
            QSqlRecord R = myQ.record();
            for (int i = 0; i<R.count(); i++)
            {
                if (i!=R.count()-1)
                    std::cout << std::setw(10)<< std::left << R.fieldName(i).toStdString().c_str() << "|";
                else
                    std::cout << std::setw(10) << std::left << R.fieldName(i).toStdString().c_str() << std::endl;
            }
            while (myQ.next())
            {
                QSqlRecord R = myQ.record();
                for (int i=0; i<R.count(); i++)
                {
                    QString result = R.value(i).toString();
                    if (i<R.count()-1) std::cout << std::setw(10) << std::left << result.toStdString().c_str() << "|";
                    else std::cout << std::setw(10) << std::left << result.toStdString().c_str() << std::endl;
                }
            }
        }
    }

    db.close();
    return a.exec();
}

