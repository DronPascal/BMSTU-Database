#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setParent(parent);
    createMenus();

    QGridLayout* mainLayout = new QGridLayout;

    pTablesListWidget = new tablesListWidget();
    pTableWibget = new tableWidget();
    pNotesWidget = new notesWidget();
    pConnectionWidget = new connectionWidget();
    pErrorsWidget = new errorsWidget();
    pCommandWidget = new commandWidget();
    pRunButton = new runPushButton();
    pFormatButton = new formatPushButton();

    //исполнитель запросов
    pRequestExecutor = new requestExecutor(this);

    //CONNECTS
    //установка бд для главного окна приложения(этого) для выполнения запросов
    connect(pConnectionWidget, SIGNAL(signalSetDB(QSqlDatabase*)), pRequestExecutor, SLOT(slotSetDB(QSqlDatabase*)));

    //автообновление списка таблиц
    //QTimer *updateTimer = new QTimer;
    //connect(updateTimer, SIGNAL(timeout()), pTablesListWidget, SLOT(slotSetDB()));
    //updateTimer->start(2000);

    //обновление списка таблиц и активной таблицы после обработки команды
    connect(pRequestExecutor, SIGNAL(signalUpdateTablesList()), pTablesListWidget, SLOT(slotSetDB()));
    connect(pRequestExecutor, SIGNAL(signalUpdateTablesList()), pTableWibget, SLOT(slotSetQuerryModel()));
    //выбор отображаемой таблицы из списка
    connect(static_cast<tablesListWidget*>(pTablesListWidget)->tablesNamesWidget, SIGNAL(itemClicked(QTableWidgetItem*)), pTableWibget, SLOT(slotSetTableItem(QTableWidgetItem*)));
    //нажатие Ctrl+Enter
    connect(pCommandWidget, SIGNAL(signalSendStringToNote(const QString&)), pNotesWidget, SLOT(slotSaveCmdLine(const QString&)));
    //установка бд для центральной таблицы
    connect(pConnectionWidget, SIGNAL(signalSetDB(QSqlDatabase*)), pTableWibget, SLOT(slotSetDB(QSqlDatabase*)));
    //обновление списка таблиц бд при подключении к бд
    connect(pConnectionWidget, SIGNAL(signalSetDB(QSqlDatabase*)), pTablesListWidget, SLOT(slotSetDB(QSqlDatabase*)));
    connect(pConnectionWidget, SIGNAL(signalSetDB(QSqlDatabase*)), pConnectionWidget, SLOT(hide()));
    //отправка запроса исполнителю
    connect(pCommandWidget, SIGNAL(signalSendString(const QString&)), pRequestExecutor, SLOT(slotExecuteString(const QString&)));
    //отправка сообщения ошибки в поле errors
    connect(pRequestExecutor, SIGNAL(signalSendError(const QString&)), pErrorsWidget, SLOT(slotAddError(const QString&)));
    //run button
    connect(pRunButton, SIGNAL(clicked()), pCommandWidget, SLOT(slotSendString()));
    //отображение заселекченной таблицы
    //connect(pRequestExecutor, SIGNAL(signalSendTable(const QString&)), pTableWibget, SLOT(slotSetTableName(const QString&)));
    //изменение модели таблицы на заселекченную таблицу
    connect(pRequestExecutor, SIGNAL(signalSendQuerryModel(QSqlQueryModel*)), pTableWibget, SLOT(slotSetQuerryModel(QSqlQueryModel*)));

    //COMPOSITION
    QSplitter *hSplitter = new QSplitter(Qt::Horizontal);
    pConnectionWidget->setMinimumWidth(300);

    hSplitter->addWidget(pTablesListWidget);
    hSplitter->addWidget(pTableWibget);
    hSplitter->addWidget(pNotesWidget);
    hSplitter->setStretchFactor(0,1);
    hSplitter->setStretchFactor(1,3);
    hSplitter->setStretchFactor(2,1);

    QSplitter *vSplitter = new QSplitter(Qt::Vertical);
    vSplitter->addWidget(hSplitter);
    vSplitter->addWidget(pErrorsWidget);

    QVBoxLayout *buttonsLayout = new QVBoxLayout;
    buttonsLayout->setContentsMargins(0,0,0,0);
    buttonsLayout->addWidget(pFormatButton);
    buttonsLayout->addWidget(pRunButton);
    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->setContentsMargins(0,0,0,0);
    bottomLayout->addWidget(pCommandWidget);
    bottomLayout->addLayout(buttonsLayout);
    QWidget *bottomWidget = new QWidget;
    bottomWidget->setLayout(bottomLayout);

    vSplitter->addWidget(bottomWidget);
    vSplitter->setStretchFactor(0,1);
    vSplitter->setStretchFactor(1,1);
    vSplitter->setStretchFactor(2,2);

    pNotesWidget->adjustSize();
    pErrorsWidget->adjustSize();
    pCommandWidget->adjustSize();
    pTablesListWidget->adjustSize();

    mainLayout->addWidget(vSplitter);

    QWidget *pMainWidget = new QWidget;
    pMainWidget->setLayout(mainLayout);
    setCentralWidget(pMainWidget);
    setStyleSheet("background-color: rgb(235,238,243);"
                  "border-color: rgb(50,104,144);");
}

MainWindow::~MainWindow()
{
}

void MainWindow::createMenus()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&Menu"));
    fileMenu->addAction(tr("&Connect..."), this, &MainWindow::openConnectionWidget);

    QAction *exitAct = fileMenu->addAction(tr("&Exit"), this, &QWidget::close);
    exitAct->setShortcuts(QKeySequence::Close);
}

void MainWindow::openConnectionWidget()
{
    pConnectionWidget->show();
}

