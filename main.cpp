/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: main.cpp
 *  简要描述:
 *
 *  创建日期: 2016-6-21
 *  作者: Yang Zhizhuang
 *  说明:
 *
 *  修改日期:
 *  作者:
 *  说明:
 *
 *  Version: 1.0
 ****************************************************************************************/
#include "./window/mainwindow.h"
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
