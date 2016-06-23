/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: sqlite.cpp
 *  简要描述:
 *
 *  创建日期: 2016-6-22
 *  作者: Yang Zhizhuang
 *  说明:
 *
 *  修改日期:
 *  作者:
 *  说明:
 ****************************************************************************************/
#include "sqlite.h"
#include "helper.h"
#include <iostream>
#include <string>
Sqlite::Sqlite()
{
    dbconn=QSqlDatabase::addDatabase("QSQLITE");    //添加数据库驱动
    dbconn.setDatabaseName("mytest.db");  //在工程目录新建一个mytest.db的文件
    if(!dbconn.open())    {
        exit(-1);
    }
}

Sqlite::~Sqlite()
{
    dbconn.close();
}

bool Sqlite::queryexec(const char* sqltext)
{
    QSqlQuery query;
    if(!query.exec(sqltext))
        return false;
    return true;
}

bool Sqlite::checkpassword(const char *username,const char *password)
{
    QSqlQuery query;
    QString u=username;
    QString sqltext="select password,salt from users where username='"+u+"'";
    query.exec(sqltext);
    query.next();
    QString pass=query.value(0).toString();
    QString salt=query.value(1).toString();
    QString tohash=password+salt;
    if(pass==Helper::hash(Helper::tochararray(tohash)))
        return true;
    else
        return false;
}

bool Sqlite::reguser(const char* username,const char* password,char* vip)//salt,regdate,sha-256
{
    QSqlQuery query;
    char* salt=Helper::getsalt();
    char* tohash=(char*)malloc(sizeof(char)*(Helper::lenofchararrau(password)+8+1));
    strcpy(tohash,password);
    strcat(tohash,salt);
    QString u=username;
    QString p=Helper::hash(tohash);
    QString s=salt;
    QString v=vip;
    QString d=Helper::getDateTime();
    QString sqltext="insert into users (username,password,salt,regdate,vip) values('"+u+"','"+p+"','"+s+"','"+d+"',"+v+")";
    if(!query.exec(sqltext))
        return false;
    QString sqltext2="create table "+u+" (uid integer PRIMARY KEY autoincrement,username varchar(10) UNIQUE,status int)";
    if(!query.exec(sqltext2))
        return false;
    return true;
}
