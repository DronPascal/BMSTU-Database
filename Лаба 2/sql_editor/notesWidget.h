#pragma once
#include <QWidget>
#include <QTextEdit>
#include <QLayout>
#include "mainwindow.h"
#include <QTextEdit>


class notesWidget : public QWidget
{
    Q_OBJECT
    friend class MainWindow;
private:
    QTextEdit *note1;
    QTextEdit *note2;
    QTextEdit *note3;
    QTextEdit *note4;
public:
    notesWidget(QWidget *parent = nullptr)
    {
        setParent(parent);
        note1 = new QTextEdit;
        note2 = new QTextEdit;
        note3 = new QTextEdit;
        note4 = new QTextEdit;
        note1->setReadOnly(1);
        note2->setReadOnly(1);
        note3->setReadOnly(1);
        note4->setReadOnly(1);

        QLabel *label; label = new QLabel("Notes");
        label->setAlignment(Qt::AlignHCenter);
        QVBoxLayout *notesLayout = new QVBoxLayout;
        notesLayout->addWidget(label);
        notesLayout->addWidget(note1);
        notesLayout->addWidget(note2);
        notesLayout->addWidget(note3);
        notesLayout->addWidget(note4);

        notesLayout->setContentsMargins(0,0,0,0);
        setLayout(notesLayout);
    }
public slots:
    void slotSaveCmdLine(const QString& text)
    {
        static int curNote=1;
        if (curNote==1) note1->setText(text);
        else if (curNote==2) note2->setText(text);
        else if (curNote==3) note3->setText(text);
        else if (curNote==4) note4->setText(text);
        curNote++;
        if (curNote>4) curNote=1;
    }
};
