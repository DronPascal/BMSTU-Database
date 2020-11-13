#pragma once

#include <QWidget>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QString>
#include <QDebug>
#include <QSqlField>
#include <QSqlQueryModel>

class requestExecutor : public QObject
{
    Q_OBJECT
private:
    QSqlDatabase *db = nullptr;
    QSqlQueryModel* qtQuerryModel;
public:
    requestExecutor(QObject *parent = nullptr)
    {
        setParent(parent);
    }
public slots:
    void slotSetDB(QSqlDatabase* new_db)
    {
        db = new_db;
    }

    void slotExecuteString(const QString& request)
    {
        if (db)
        {
            QSqlQuery myQ(*db);
            QString res = request;
            QStringList requestsList = res.split(";");

            for (auto cur_request : requestsList)
            {
                myQ.exec(cur_request);
                if (myQ.isActive())
                {
                    if (myQ.isSelect())
                    {
                        qtQuerryModel = new QSqlQueryModel();
                        qtQuerryModel->setQuery(myQ);
                        emit signalSendQuerryModel(qtQuerryModel);
                        emit signalSendError("Selected!");
                        return;
                    }
                    else emit signalSendError("Success!");
                }
                else
                {
                    emit signalSendError(myQ.lastError().text());
                    emit signalUpdateTablesList();
                    return;
                }
            }
        }
        emit signalUpdateTablesList();
    }

signals:
    void signalSendError(const QString&);
    void signalUpdateTablesList();
    void signalSendTable(const QString&);
    void signalSendQuerryModel(QSqlQueryModel*);
};
