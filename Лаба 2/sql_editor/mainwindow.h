#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QGridLayout>
#include <QSplitter>
#include <QWidget>
#include <QSqlQuery>
#include <QMenu>
#include <QMenuBar>

#include "tablesListWidget.h"
#include "QtTableWidget.h"
#include "connectionWidget.h"
#include "commandWidget.h"
#include "errorsWidget.h"
#include "notesWidget.h"
#include "myPushButtons.h"
#include "requestExecutor.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
     void createMenus();

     QWidget *pTablesListWidget;
     QWidget *pTableWibget;
     QWidget *pNotesWidget;
     QWidget *pConnectionWidget;
     QWidget *pErrorsWidget;
     QWidget *pCommandWidget;
     QPushButton *pRunButton;
     QPushButton *pFormatButton;
     //исполнитель запросов
     QObject *pRequestExecutor;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void openConnectionWidget();

};
#endif // MAINWINDOW_H
