#pragma once
#include <QWidget>
#include <QTextEdit>
#include <QLayout>
#include <mainwindow.h>

#include <QtCore>
#include <QtGui>
#include <QPushButton>

class MyPushButton : public QPushButton{
    Q_OBJECT
public:
    QFont font;

    MyPushButton(QPushButton* parent = nullptr) :
        QPushButton(parent)
    {
        setFont(font);
        setText("1");
    }

    MyPushButton(QString const &str, QPushButton* parent = nullptr) :
        QPushButton(parent)
    {
        setFont(font);
        setText(str);
    }

    void resizeEvent(QResizeEvent *event)
    {
        Q_UNUSED(event)
        font.setPixelSize(int(this->size().width() / 3.5));
        setFont(font);
    }
};

class runPushButton : public MyPushButton
{
    Q_OBJECT
    friend class BDEditor;
public:
    runPushButton(QWidget *parent = nullptr)
    {
        setParent(parent);
        setText("Run");
        setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        setMinimumWidth(170);
    }
};

class formatPushButton : public MyPushButton
{
    Q_OBJECT
    friend class BDEditor;
public:
    formatPushButton(QWidget *parent = nullptr)
    {
        setParent(parent);
        setText("Format");
        setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        setMinimumWidth(170);
    }
};

class hystoryPushButton : public MyPushButton
{
    Q_OBJECT
    friend class BDEditor;
public:
    hystoryPushButton(QWidget *parent = nullptr)
    {
        setParent(parent);
        setText("Format");
        setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        setMinimumWidth(170);
    }
};


