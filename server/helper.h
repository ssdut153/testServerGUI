/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: helper.h
 *  简要描述:
 *
 *  创建日期: 2016-6-22
 *  作者: Yang Zhizhuang
 *  说明:
 *
 *  修改日期: 2016-6-23
 *  作者: Yang Zhizhuang
 *  说明: 增加getLogFileName函数和log函数以及getLogPath函数
 ****************************************************************************************/
#ifndef HELPER_H
#define HELPER_H
#include<iostream>
#include<QString>
class Helper
{
public:
    static QString hash(QString text);
    static const char* tochararray(QString qstr);
    static char randchar(int rule);
    static int randint(int lower,int higher);
    static char* getsalt(int length=8);
    static int lenofchararrau(const char* text);
    static QString getHeadfromJson(QByteArray textJson);
    static QString getDateTime();
    static QString getLogFileName(QString logPath);
    static bool log(QString logText,QString logPath);
    static void getLogPath(char* logPath);
    static QString newuuid();
};

#endif // HELPER_H
