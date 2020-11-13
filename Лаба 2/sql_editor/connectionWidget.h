#pragma once
#include <QWidget>
#include <QLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include "mainwindow.h"

#include <QtSql>
#include <QDebug>
#include <QMessageBox>

class connectionWidget : public QWidget
{
    Q_OBJECT
    friend class MainWindow;
    friend class commandWidget;
private:
    QLabel *ipLabel;
    QLabel *portLabel;
    QLabel *loginLabel;
    QLabel *passwordLabel;
    QLabel *dbNameLabel;

    QLineEdit *ipEdit;
    QLineEdit *portEdit;
    QLineEdit *loginEdit;
    QLineEdit *passwordEdit;
    QLineEdit *dbNameEdit;

    QPushButton *connectButton;
    QPushButton *presetButton1;
    QPushButton *presetButton2;

    QSqlDatabase db;
public:
    connectionWidget(QWidget *parent = nullptr)
    {
        setParent(parent);
        ipEdit = new QLineEdit;
        portEdit = new QLineEdit;
        loginEdit = new QLineEdit;
        passwordEdit = new QLineEdit;
        dbNameEdit = new QLineEdit;


        ipLabel = new QLabel(tr("IP:"));
        portLabel = new QLabel(tr("Port:"));
        loginLabel = new QLabel(tr("Login:"));
        passwordLabel = new QLabel(tr("Password:"));
        dbNameLabel = new QLabel(tr("DB Name:"));

        connectButton = new QPushButton(tr("Connect"));
        presetButton1 = new QPushButton(tr("Preset 1"));
        presetButton2 = new QPushButton(tr("Preset 2"));

        QGridLayout *connectLayout = new QGridLayout;
        connectLayout->addWidget(ipLabel, 0, 0);
        connectLayout->addWidget(portLabel, 1, 0);
        connectLayout->addWidget(loginLabel, 2, 0);
        connectLayout->addWidget(passwordLabel, 3, 0);
        connectLayout->addWidget(dbNameLabel, 4, 0);

        connectLayout->addWidget(ipEdit, 0, 1);
        connectLayout->addWidget(portEdit, 1, 1);
        connectLayout->addWidget(loginEdit, 2, 1);
        connectLayout->addWidget(passwordEdit, 3, 1);
        connectLayout->addWidget(dbNameEdit, 4, 1);

        QGridLayout *buttonsLayout = new QGridLayout;
        buttonsLayout->setContentsMargins(0,0,0,0);
        buttonsLayout->addWidget(presetButton1, 0, 0);
        buttonsLayout->addWidget(presetButton2, 0, 1);
        buttonsLayout->addWidget(connectButton, 1, 0, 1, 2);

        connectLayout->addLayout(buttonsLayout, 5,0,1,2);


        setLayout(connectLayout);
        //CONNECTS
        connect(presetButton1, SIGNAL(clicked()), SLOT(slotPreset1()));
        connect(presetButton2, SIGNAL(clicked()), SLOT(slotPreset2()));
        connect(connectButton, SIGNAL(clicked()), SLOT(slotConnectToDB()));
    }
    ~connectionWidget()
    {
        db.close();
    }
public slots:
    void slotConnectToDB()
    {
        QSqlDatabase new_db;
        if (ipEdit->text() == "localhost" && dbNameEdit->text() != "psql")
        {
            new_db = QSqlDatabase::addDatabase("QSQLITE");
            new_db.setDatabaseName(dbNameEdit->text());
        }
        else if (ipEdit->text() == "localhost" && dbNameEdit->text() == "psql")
        {
            new_db = QSqlDatabase::addDatabase("QPSQL");
            new_db.setDatabaseName(dbNameEdit->text());
        }
        else
        {
            new_db = QSqlDatabase::addDatabase("QPSQL");
            new_db.setHostName(ipEdit->text());
            new_db.setPort(portEdit->text().toInt());
            new_db.setUserName(loginEdit->text());
            new_db.setPassword(passwordEdit->text());
            new_db.setDatabaseName(dbNameEdit->text());
        }

        if (!new_db.open())
        {
            QMessageBox::warning(nullptr, qApp->applicationName(),QString("Не удалось подключиться к базе данных").arg(db.databaseName()));
            hide();
        }
        else
        {
            db = new_db;
            emit signalSetDB(&db);
        }
    }

    void slotPreset1()
    {
        ipEdit->setText("195.19.32.74");
        portEdit->setText("5432");
        loginEdit->setText("student");
        passwordEdit->setText("bmstu");
        dbNameEdit->setText("fn1132_2019");
    }
    void slotPreset2()
    {
        ipEdit->setText("localhost");
        portEdit->setText("");
        loginEdit->setText("");
        passwordEdit->setText("");
        dbNameEdit->setText("MyTestDB");
    }
signals:
    void signalSetDB(QSqlDatabase*);
};

