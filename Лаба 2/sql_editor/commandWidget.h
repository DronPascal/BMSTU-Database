#pragma once
#include <QWidget>
#include <QTextEdit>
#include <QLayout>
#include <mainwindow.h>
#include <QShortcut>
#include "sqlHighlighter.h"

class commandWidget : public QWidget
{
    Q_OBJECT
    friend class MainWindow;
private:
    SqlHighlighter *m_SQLHighLighter;
    QTextEdit *commandLine;
    QShortcut *CtrlEnter = new QShortcut(Qt::CTRL + Qt::Key_Return, this);
    QShortcut *Return = new QShortcut(Qt::CTRL + Qt::Key_0, this);
public:
    commandWidget(QWidget *parent = nullptr)
    {
        setParent(parent);
        commandLine = new QTextEdit;
        //style
        commandLine->setStyleSheet("QTextEdit{"
                                   "    font-size: 16px;}");
        commandLine->setFontFamily("Yugothic");
        m_SQLHighLighter = new SqlHighlighter(commandLine->document());

        QBoxLayout *commandLayout = new QBoxLayout(QBoxLayout::LeftToRight);
        commandLayout->addWidget(commandLine);
        setLayout(commandLayout);
        commandLayout->setContentsMargins(0,0,0,0);

        //CONNECTS
        connect(CtrlEnter, SIGNAL(activated()), SLOT(slotSendStringToNote()));
        connect(Return, SIGNAL(activated()), SLOT(slotSendString()));
    }
public slots:
    void slotSendString()
    {
        emit signalSendString(commandLine->toPlainText());
    }
    void slotSendStringToNote()
    {
        emit signalSendStringToNote(commandLine->toPlainText());
    }
    void slotGetString(QString *request)
    {
        commandLine->setText(*request);
    }
signals:
    void signalSendString(const QString&);
    void signalSendStringToNote(const QString&);

};

