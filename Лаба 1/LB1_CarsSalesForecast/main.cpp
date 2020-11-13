#include <QCoreApplication>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlRecord>
#include <QDebug>
#include <QSqlError>

#include <iostream>
#include <iomanip>
#include <string>
#include "stdlib.h"
int main(int argc, char* argv[])
{
    setlocale(0, "russian");
    QCoreApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("PasShiDB1");
    if (!db.open())
    {
        std::cout << "DB is not opened" << std::endl;
        return a.exec();
    }
    QSqlQuery myQ(db);

    myQ.exec("PRAGMA foreign_keys = ON");

    myQ.exec("DROP TABLE car_manufacturers");
    myQ.exec("DROP TABLE sales_forecast");
    myQ.exec("DROP TABLE sanctions");
    myQ.exec("DROP TABLE sanctions_losses");

    myQ.exec("CREATE TABLE car_manufacturers ("
        "model varchar[20] NOT NULL PRIMARY KEY,"
        "manufacturer varchar[15] NOT NULL,"
        "country varchar[15] NOT NULL"
        ")");

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
        "('Audi Q8','Audi','Germany')");

    myQ.exec("CREATE TABLE sales_forecast ("
        "model varchar[20] NOT NULL REFERENCES car_manufacturers(model) ON DELETE CASCADE,"
        "year smallint NOT NULL,"
        "price numeric(15, 2) NOT NULL"
        ")");

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


    myQ.exec("CREATE TABLE sanctions ("
        "country varchar[15] NOT NULL,"
        "starting_year smallint NOT NULL"
        ")");

    myQ.exec("INSERT INTO sanctions (country, starting_year)"
        "VALUES ('USA', 2016),"
        "('Japan', 2017),"
        "('Germany', 2018)");

    myQ.exec("CREATE TABLE sanctions_losses ("
        "manufacturer varchar[15] UNIQUE,"
        "country varchar[15],"
        "loss_percentage dec(6, 4)"
        ")");

    myQ.exec("INSERT INTO sanctions_losses (manufacturer, country) "
        "SELECT DISTINCT manufacturer, country AS cm_country "
        "  FROM car_manufacturers"
        "      WHERE EXISTS (SELECT * FROM sanctions WHERE sanctions.country=cm_country)");

    myQ.exec("UPDATE sanctions_losses "
        "SET loss_percentage=(( "
        "  SELECT SUM(price) "
        "  FROM sales_forecast "
        "      WHERE year>=(SELECT starting_year FROM sanctions WHERE country=sanctions_losses.country) "
        "      AND "
        "      EXISTS (SELECT model FROM car_manufacturers "
        "                  WHERE manufacturer=sanctions_losses.manufacturer AND model=sales_forecast.model) "
        "  )*100.)/("
        "  SELECT SUM(price) "
        "  FROM sales_forecast "
        "      WHERE EXISTS (SELECT model FROM car_manufacturers WHERE manufacturer=sanctions_losses.manufacturer AND model=sales_forecast.model))");

    /*
select * from sanctions_losses
    */
    myQ.exec("CREATE TABLE tables");
    myQ.exec("INSERT INTO tables SELECT SHOW TABLES");

    std::cout << myQ.lastError().text().toStdString() << std::endl;

    //#1      UPDATE per SET pers=((SELECT SUM(price) FROM sales_forecast WHERE year>=(SELECT starting_year FROM sanctions WHERE country=per.cy) AND EXISTS (SELECT model AS mod FROM car_manufacturers WHERE manufacturer=per.mf AND model=mod))*100) / (SELECT SUM(price) FROM sales_forecast WHERE EXISTS (SELECT model AS mod FROM car_manufacturers WHERE manufacturer=mf AND model=mod))
    //#2      UPDATE per SET pers=((SELECT SUM(price) FROM sales_forecast WHERE year>=(SELECT starting_year FROM sanctions WHERE country=per.cy) AND EXISTS (SELECT model AS mod FROM car_manufacturers WHERE manufacturer=per.mf AND sales_forecast.model=mod))*100) / (SELECT SUM(price) FROM sales_forecast WHERE EXISTS (SELECT model AS mod FROM car_manufacturers WHERE manufacturer=mf AND sales_forecast.model=mod))


    std::string command = " ";
    while (command != "exit")
    {
        std::cout << "Enter command: ";
        std::getline(std::cin, command);
        myQ.exec(command.c_str());

        /*
        QSqlQuery query;
        query.exec("SELECT stock FROM employee WHERE id = ?");

        if (query.next()) {
            int stock = query.value(0).toInt();
        */

        if (myQ.isActive()) {
            if (myQ.isSelect())
            {
                std::cout << "TABLE Selected\n";
                QSqlRecord R = myQ.record();
                for (int i = 0; i < R.count(); i++)
                {
                    if (i != R.count() - 1)
                        std::cout << std::setw(25) << std::left << R.fieldName(i).toStdString().c_str() << "|";
                    else
                        std::cout << std::setw(25) << std::left << R.fieldName(i).toStdString().c_str() << std::endl;
                }
                std::cout << "-------------------------|-------------------------|-------------------------" << std::endl;
                while (myQ.next())
                {
                    QSqlRecord R = myQ.record();
                    for (int i = 0; i < R.count(); i++)
                    {
                        QString result = R.value(i).toString();
                        if (i < R.count() - 1) std::cout << std::setw(25) << std::left << result.toStdString().c_str() << "|";
                        else std::cout << std::setw(25) << std::left << result.toStdString().c_str() << std::endl;
                    }
                }
                std::cout << std::endl;
            }
            else {
                std::cout << "OK" << std::endl;
            }
        }
        else {
            if (command != "exit")
                std::cout << myQ.lastError().text().toStdString() << std::endl;
        }
    }

    db.close();
    db.removeDatabase("PasShiDB1");
    return a.exec();
}
