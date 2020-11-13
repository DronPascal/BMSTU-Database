#pragma once
#include <QWidget>
#include <QTableView>
#include <QTableWidget>
#include <QLayout>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QLabel>

class tableWidget : public QWidget
{
    Q_OBJECT
private:
    QSqlTableModel *pModel;
    QTableView *pView;
public:
    tableWidget(QWidget *parent = nullptr)
    {
        setParent(parent);
        pModel = new QSqlTableModel();
        pView = new QTableView;

        QLabel *label; label = new QLabel("Selected table");
        label->setAlignment(Qt::AlignHCenter);
        QVBoxLayout *tableLayout = new QVBoxLayout;
        tableLayout->addWidget(label);
        tableLayout->addWidget(pView);
        tableLayout->setContentsMargins(0,0,0,0);

        setLayout(tableLayout);
    }
public slots:
    void slotSetDB(QSqlDatabase* new_db)
    {
        delete pModel;
        pModel = new QSqlTableModel(nullptr, *new_db);
    }
    void slotSetTableItem(QTableWidgetItem* tableItem)
    {
        pModel->setTable(QString(tableItem->text()));
        pModel->select();
        pView->setModel(pModel);
        pView->resizeColumnsToContents();
    }
    void slotSetTableName(const QString& tableName)
    {
        pModel->setTable(tableName);
        pModel->select();
        pView->setModel(pModel);
        pView->resizeColumnsToContents();
    }
    void slotSetQuerryModel(QSqlQueryModel* model = nullptr)
    {
        if  (model)
            pView->setModel(model);
        else
        {
            pModel->select();
            pView->setModel(pModel);
        }
        pView->resizeColumnsToContents();
    }
};
