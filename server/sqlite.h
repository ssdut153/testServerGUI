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
#include <QtNetwork>
#include <vector>
#include "myclient.h"
class Sqlite
{
public:
    Sqlite();
    ~Sqlite();
    bool checkpassword(const char* username,const char* password);
    bool reguser(const char* username,const char* password,const char* vip);//salt,regdate,sha-256
    bool queryexec(const char* sqltext);
    char* select1(char* selecttext);
    bool sendfriendlist(const char* username,QTcpSocket* client);
    bool isfriend(const char* username,const char* tocheckuser);
    bool updatelogin(const char* username);
    bool updatelogout(const char* username);
    bool isonline(const char* username);
    bool sendtofriends(const char* username,bool online,std::vector<MyClient>& clients,int size);
    bool inital();
    bool login(const char* username,QString ip);
    bool isexist(const char* username);
private:
    QSqlDatabase dbconn;
    QString regusersql="insert into users (username,password,salt,regdate,vip) values('?','?','?','?',?)";
    QString checkpasswordsql="select password,salt from users where username=':user'";
};

#endif // SQLITE_H
