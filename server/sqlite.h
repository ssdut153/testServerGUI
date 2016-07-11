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
#include <QByteArray>
#include "myclient.h"
#include "../common/message/addfriend/ajfriendmessage.h"
class Sqlite
{
public:
    Sqlite();
    ~Sqlite();
    bool checkpassword(QString username, QString password);
    bool reguser(QString username,QString password,QString vip);//salt,regdate,sha-256
    bool queryexec(QString sqltext);
    QString select1(QString selecttext);
    bool sendfriendlist(QString username,QTcpSocket* client);
    bool isfriend(QString username,QString tocheckuser);
    bool updatelogin(QString username);
    bool updatelogout(QString username);
    bool isonline(QString username);
    bool sendtofriends(QString username,bool online,std::vector<MyClient>& clients,int size);
    bool inital();
    bool login(QString username,QString ip);
    bool isexist(QString username);
    bool addfriend(QString fromusername,QString tousername);
    bool ajfriend(ajFriendMessage& ajfriendmessage);
    bool logofflinemessage(QString fromusername,QString tousername,QString createtime,QString content);
    QByteArray getofflinemessage(QString username);
private:
    QSqlDatabase dbconn;
    QString regusersql="insert into users (username,password,salt,regdate,vip) values('?','?','?','?',?)";
    QString checkpasswordsql="select password,salt from users where username=':user'";
};

#endif // SQLITE_H
