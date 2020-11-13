#pragma once
#include <QWidget>
#include <QTextEdit>
#include <QLayout>
#include <mainwindow.h>

class errorsWidget : public QWidget
{
    Q_OBJECT
    friend class MainWindow;
private:
    QTextEdit *errorsLine;
public:
    errorsWidget(QWidget *parent = nullptr)
    {
        setParent(parent);
        errorsLine = new QTextEdit;
        errorsLine->setReadOnly(true);
        errorsLine->setText("Errors are sent here\n");

        QBoxLayout *errorsLayout = new QBoxLayout(QBoxLayout::LeftToRight);
        errorsLayout->addWidget(errorsLine);
        errorsLayout->setContentsMargins(0,0,0,0);

        setLayout(errorsLayout);
    }
public slots:
    void slotAddError(const QString& error)
    {
        errorsLine->insertPlainText(error+"\n");
        errorsLine->moveCursor(QTextCursor::End);
    }
};
