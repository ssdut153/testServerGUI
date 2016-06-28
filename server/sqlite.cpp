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
#include "./common/allmessage.h"
#include <iostream>
#include <string>
//insert into testuser2 (username,status) values('testuser1',1)
/**
 * @brief Sqlite::Sqlite
 */
Sqlite::Sqlite()
{
    dbconn=QSqlDatabase::addDatabase("QSQLITE");    //添加数据库驱动
    dbconn.setDatabaseName("mytest.db");  //在工程目录新建一个mytest.db的文件
    if(!dbconn.open())    {
        exit(-1);
    }
}
/**
 * @brief Sqlite::~Sqlite
 */
Sqlite::~Sqlite()
{
    dbconn.close();
}
bool Sqlite::ajfriend(ajFriendMessage& ajfriendmessage)
{
    if(ajfriendmessage.acpt=="true")
    {
        QSqlQuery query;
        QString u=QString::fromStdString(ajfriendmessage.fromuser);
        QString t=QString::fromStdString(ajfriendmessage.touser);
        QString sqltext="update "+u+" set status=1 where username='"+t+"'";
        if(!query.exec(sqltext))
            return false;
        QString sqltext2="update "+t+" set status=1 where username='"+u+"'";
        if(!query.exec(sqltext2))
            return false;
        //TODO:发送新好友通知
        return true;
    }
    else
    {
        QSqlQuery query;
        QString u=QString::fromStdString(ajfriendmessage.fromuser);
        QString t=QString::fromStdString(ajfriendmessage.touser);
        QString sqltext="delete from "+u+" where username='"+t+"'";
        if(!query.exec(sqltext))
            return false;
        QString sqltext2="delete from "+t+" where username='"+u+"'";
        if(!query.exec(sqltext2))
            return false;
        return true;
    }
}

bool Sqlite::addfriend(const char* fromusername,const char* tousername)
{
    QSqlQuery query;
    QString u=fromusername;
    QString t=tousername;
    QString sqltext="insert into "+t+" (username,status) values('"+u+"',0)";
    if(!query.exec(sqltext))
        return false;
    QString sqltext2="insert into "+u+" (username,status) values('"+t+"',0)";
    if(!query.exec(sqltext2))
        return false;
    return true;
}

bool Sqlite::isfriend(const char* username,const char* tocheckuser)
{
    QSqlQuery query;
    QString u=username;
    QString t=tocheckuser;
    QString sqltext="select * from "+u+" where username='"+t+"'";
    if(!query.exec(sqltext))
        return false;
    if(query.next())
        return true;
    else
        return false;
}

/**
 * @brief Sqlite::queryexec
 * @param sqltext sql语句
 * @return bool
 */
bool Sqlite::queryexec(const char* sqltext)
{
    QSqlQuery query;
    if(!query.exec(sqltext))
        return false;
    return true;
}

bool Sqlite::updatelogin(const char* username)
{
    QSqlQuery query;
    QString u=username;
    QString sqltext="update users set logindate='"+Helper::getDateTime()+"' where username='"+u+"'";
    if(!query.exec(sqltext))
        return false;
    QString sqltext2="update users set online=1 where username='"+u+"'";
    if(!query.exec(sqltext2))
        return false;
    return true;
}
bool Sqlite::updatelogout(const char* username)
{
    QSqlQuery query;
    QString u=username;
    QString sqltext2="update users set online=0 where username='"+u+"'";
    if(!query.exec(sqltext2))
        return false;
    return true;
}
bool Sqlite::isonline(const char* username)
{
    QSqlQuery query;
    QString u=username;
    QString sqltext="select online from users where username='"+u+"'";
    if(!query.exec(sqltext))
        return false;
    if(!query.next())
        return false;
    if(query.value(0).toInt()==1)
        return true;
    else
        return false;
}
bool Sqlite::inital()
{
    QSqlQuery query;
    QString sqltext="update users set online=0";
    if(!query.exec(sqltext))
        return false;
    return true;
}

bool Sqlite::sendtofriends(const char* username,bool online,std::vector<MyClient>& clients,int size)
{
    QSqlQuery query;
    QString u=username;
    QString sqltext="select username from "+u+" where status=1";
    if(!query.exec(sqltext))
        return false;
    //try{
    while(query.next())//query.next()指向查找到的第一条记录，然后每次后移一条记录
    {
        QTcpSocket* tempSocket=NULL;
        QString ele0=query.value(0).toString();
        if(isonline(ele0.toStdString().c_str()))
        {
            bool flag=false;
            for(int i=0;i<size;i++)
            {
                if(clients[i].username==ele0.toStdString())
                {
                    tempSocket=clients[i].client;
                    flag=true;
                    break;
                }
            }
            if(flag)
            {
                if(online)
                {
                    onlineMessage onlinemessage(username);
                    tempSocket->write(onlinemessage.getJsonString().c_str());
                }
                else
                {
                    offlineMessage offlinemessage(username);
                    tempSocket->write(offlinemessage.getJsonString().c_str());
                }
            }
            else
                continue;
        }
        else
            continue;
    }
    //}
    //catch(...)
    //{
    //    return false;
    // }

    return true;
}
bool Sqlite::isexist(const char* username)
{
    QSqlQuery query;
    QString u=username;
    QString sqltext="select * from users where username='"+u+"'";
    if(!query.exec(sqltext))
        return false;
    if(!query.next())
        return false;
    return true;
}

/**
 * @brief Sqlite::sendfriendlist
 * @param username 用户名
 * @param client QTcpSocket*
 * @return bool
 */
bool Sqlite::sendfriendlist(const char* username,QTcpSocket* client)
{
    QSqlQuery query;
    QString u=username;
    QString sqltext="select username from "+u+" where status=1";
    if(!query.exec(sqltext))
        return false;
    startSendListMessage startsendlistmessage;
    client->write(startsendlistmessage.getJsonString().c_str());
    client->waitForBytesWritten();
    friendListMessage friendlistmessage;
    while(query.next())//query.next()指向查找到的第一条记录，然后每次后移一条记录
    {
        QString ele0=query.value(0).toString();//query.value(0)是id的值，将其转换为int型
        friendlistmessage.adduser(ele0.toStdString(),isonline(ele0.toStdString().c_str())?1:0);
    }
    client->write(friendlistmessage.getJsonString().c_str());
    //client->waitForBytesWritten();
    //endSendListMessage endsendlistmessage;
    //client->write(endsendlistmessage.getJsonString().c_str());
    return true;
}
/**
 * @brief Sqlite::checkpassword
 * @param username 用户名
 * @param password 密码
 * @return bool
 */
bool Sqlite::checkpassword(const char *username,const char *password)
{
    QSqlQuery query;
    QString u=username;
    QString sqltext="select password,salt from users where username='"+u+"'";
    if(!query.exec(sqltext))
        return false;
    query.next();
    QString pass=query.value(0).toString();
    QString salt=query.value(1).toString();
    QString tohash=password+salt;
    if(pass==Helper::hash(Helper::tochararray(tohash)))
        return true;
    else
        return false;
}
bool Sqlite::login(const char* username,QString ip)
{
    QSqlQuery query;
    QString u=username;
    QString sqltext="update users set ip='"+ip+"' where username='"+u+"'";
    if(!query.exec(sqltext))
        return false;
    else
        return true;
}

/**
 * @brief Sqlite::reguser
 * @param username 用户名
 * @param password 密码
 * @param vip 是否为vip(0,1)
 * @return bool
 */
bool Sqlite::reguser(const char* username,const char* password,const char* vip)//salt,regdate,sha-256
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
    QString sqltext="insert into users (username,password,salt,regdate,vip,online) values('"+u+"','"+p+"','"+s+"','"+d+"',"+v+",0)";
    if(!query.exec(sqltext))
        return false;
    QString sqltext2="create table "+u+" (uid integer PRIMARY KEY autoincrement,username varchar(10) UNIQUE,status int)";
    if(!query.exec(sqltext2))
        return false;
    return true;
}
