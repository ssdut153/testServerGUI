/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: sqlite.h
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
#ifndef SQLITE_H
#define SQLITE_H

#include <QtSql>
#include <QString>
class Sqlite
{
public:
    Sqlite();
    ~Sqlite();
    bool checkpassword(const char* username,const char* password);
    bool reguser(const char* username,const char* password,char* vip);//salt,regdate,sha-256
    bool queryexec(const char* sqltext);
    char* select1(char* selecttext);
private:
    QSqlDatabase dbconn;
    QString regusersql="insert into users (username,password,salt,regdate,vip) values('?','?','?','?',?)";
    QString checkpasswordsql="select password,salt from users where username=':user'";
};

#endif // SQLITE_H
