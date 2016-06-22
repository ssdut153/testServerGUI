#include "mainwindow.h"
#include <QApplication>
#include <QDir>
#include <QDebug>
#include <QSqlDatabase>
int main(int argc, char *argv[])
{
    QApplication::addLibraryPath("./plugins");
    QApplication a(argc, argv);


    MainWindow w;
    w.show();

    return a.exec();
}
