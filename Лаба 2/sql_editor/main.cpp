#include "mainwindow.h"

#include <QApplication>
#include <QStyleFactory>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow sql_editor;
    sql_editor.setMinimumWidth(1200);
    sql_editor.show();
    a.setStyle(QStyleFactory::create("Fusion"));
    QFontDatabase fontDatabase;
    if (fontDatabase.addApplicationFont(":/fonts/Verdana.ttf") == -1)
        qWarning() << "Failed to load Verdana.ttf";
    if (fontDatabase.addApplicationFont(":/fonts/Yugothic.ttf") == -1)
        qWarning() << "Failed to load Yugothic.ttf";
    return a.exec();
}
