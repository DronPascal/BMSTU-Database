#pragma once
#include <QWidget>
#include <QSqlDatabase>
#include "QStandardItemModel"
#include <QLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QLabel>
#include <QGroupBox>
#include <mainwindow.h>

class tablesListWidget : public QWidget
{
    Q_OBJECT
    friend class MainWindow;
private:
    QStringList list_tables;
    QTableWidget *tablesNamesWidget;
    QSqlDatabase *db = nullptr;

public:
    tablesListWidget(QWidget *parent = nullptr)
    {
        setParent(parent);
        tablesNamesWidget = new QTableWidget;
        tablesNamesWidget->setColumnCount(1);
        tablesNamesWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tablesNamesWidget->verticalHeader()->hide();
        tablesNamesWidget->horizontalHeader()->hide();
        tablesNamesWidget->resizeColumnsToContents();
        tablesNamesWidget->setColumnWidth(0,9999);
        tablesNamesWidget->setSelectionMode(QAbstractItemView::SingleSelection);

        QLabel *label; label = new QLabel("Available tables");
        label->setAlignment(Qt::AlignHCenter);
        QVBoxLayout *namesLayout = new QVBoxLayout;
        namesLayout->addWidget(label);
        namesLayout->addWidget(tablesNamesWidget);
        namesLayout->setContentsMargins(0,0,0,0);

        setLayout(namesLayout);
    }
public slots:
    void slotSetDB(QSqlDatabase* new_db = nullptr)
    {
        if (new_db)
            db = new_db;
        if (db != nullptr)
        {
            list_tables = db->tables();
            tablesNamesWidget->clear();
            tablesNamesWidget->setRowCount(list_tables.size());
            int i=0;
            for (auto iter = list_tables.begin(); iter != list_tables.end(); iter++)
            {
                QTableWidgetItem *newItem = new QTableWidgetItem(*iter);
                tablesNamesWidget->setItem(i++, 0, newItem);
            }
        }
    }
};
