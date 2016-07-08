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
        QString u=ajfriendmessage.fromuser;
        QString t=ajfriendmessage.touser;
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
        QString u=ajfriendmessage.fromuser;
        QString t=ajfriendmessage.touser;
        QString sqltext="delete from "+u+" where username='"+t+"'";
        if(!query.exec(sqltext))
            return false;
        QString sqltext2="delete from "+t+" where username='"+u+"'";
        if(!query.exec(sqltext2))
            return false;
        return true;
    }
}

bool Sqlite::addfriend(QString fromusername, QString tousername)
{
    QSqlQuery query;
    QString sqltext="insert into "+tousername+" (username,status) values('"+fromusername+"',0)";
    if(!query.exec(sqltext))
        return false;
    QString sqltext2="insert into "+fromusername+" (username,status) values('"+tousername+"',0)";
    if(!query.exec(sqltext2))
        return false;
    return true;
}

bool Sqlite::isfriend(QString username, QString tocheckuser)
{
    QSqlQuery query;
    QString sqltext="select * from "+username+" where username='"+tocheckuser+"'";
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
bool Sqlite::queryexec(QString sqltext)
{
    QSqlQuery query;
    if(!query.exec(sqltext))
        return false;
    return true;
}

bool Sqlite::updatelogin(QString username)
{
    QSqlQuery query;
    QString sqltext="update users set logindate='"+Helper::getDateTime()+"' where username='"+username+"'";
    if(!query.exec(sqltext))
        return false;
    QString sqltext2="update users set online=1 where username='"+username+"'";
    if(!query.exec(sqltext2))
        return false;
    return true;
}
bool Sqlite::updatelogout(QString username)
{
    QSqlQuery query;
    QString sqltext2="update users set online=0 where username='"+username+"'";
    if(!query.exec(sqltext2))
        return false;
    return true;
}
bool Sqlite::isonline(QString username)
{
    QSqlQuery query;
    QString sqltext="select online from users where username='"+username+"'";
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

bool Sqlite::sendtofriends(QString username,bool online,std::vector<MyClient>& clients,int size)
{
    QSqlQuery query;
    QString sqltext="select username from "+username+" where status=1";
    if(!query.exec(sqltext))
        return false;
    //try{
    while(query.next())//query.next()指向查找到的第一条记录，然后每次后移一条记录
    {
        QTcpSocket* tempSocket=NULL;
        QString ele0=query.value(0).toString();
        if(isonline(ele0))
        {
            bool flag=false;
            for(int i=0;i<size;i++)
            {
                if(clients[i].username==ele0)
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
                    tempSocket->write(onlinemessage.getJsonString());
                }
                else
                {
                    offlineMessage offlinemessage(username);
                    tempSocket->write(offlinemessage.getJsonString());
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
bool Sqlite::isexist(QString username)
{
    QSqlQuery query;
    QString sqltext="select * from users where username='"+username+"'";
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
bool Sqlite::sendfriendlist(QString username,QTcpSocket* client)
{
    QSqlQuery query;
    QString sqltext="select username from "+username+" where status=1";
    if(!query.exec(sqltext))
        return false;
    friendListMessage friendlistmessage;
    while(query.next())//query.next()指向查找到的第一条记录，然后每次后移一条记录
    {
        QString ele0=query.value(0).toString();//query.value(0)是id的值，将其转换为int型
        friendlistmessage.adduser(ele0,isonline(ele0)?1:0);
    }
    client->write(friendlistmessage.getJsonString());
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
bool Sqlite::checkpassword(QString username,QString password)
{
    QSqlQuery query;
    QString sqltext="select password,salt from users where username='"+username+"'";
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
bool Sqlite::logofflinemessage(QString fromusername,QString tousername,QString createtime,QString content)
{
    QSqlQuery query;
    QString sqltext="insert into "+tousername+"_chat"+" (fromusername,tousername,createtime,content) values('"+fromusername+"','"+tousername+"','"+createtime+"','"+content+"')";
    if(!query.exec(sqltext))
        return false;
    else
        return true;
}
QByteArray Sqlite::getofflinemessage(QString username)
{
    QSqlQuery query;
    QString sqltext="select fromusername,tousername,createtime,content from "+username+"_chat";
    if(!query.exec(sqltext))
        return "";
    query.next();
    listMessage listmessage(query.value(1).toString());
    listmessage.addOfflineMessage(query.value(0).toString(),query.value(2).toString(),query.value(3).toString());
    while(query.next())//query.next()指向查找到的第一条记录，然后每次后移一条记录
    {
        listmessage.addOfflineMessage(query.value(0).toString(),query.value(2).toString(),query.value(3).toString());
    }
    QString sqltext2="select username from "+username+" where status=0";
    if(!query.exec(sqltext2))
        return "";
    while(query.next())//query.next()指向查找到的第一条记录，然后每次后移一条记录
    {
        listmessage.addFriendRequestMessage(query.value(0).toString());
    }
    QString sqltext3="delete from "+username+"_chat";
    if(!query.exec(sqltext3))
        return "";
    return listmessage.getJsonString();
}

bool Sqlite::login(QString username,QString ip)
{
    QSqlQuery query;
    QString sqltext="update users set ip='"+ip+"' where username='"+username+"'";
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
bool Sqlite::reguser(QString username, QString password,QString vip)//salt,regdate,sha-256
{
    QSqlQuery query;
    QString salt=Helper::getsalt();
//    char* tohash=(char*)malloc(sizeof(char)*(Helper::lenofchararrau(password)+8+1));
    QString tohash =password + salt;
//    strcpy(tohash,password);
//    strcat(tohash,salt);
    QString p=Helper::hash(tohash);
    QString v=vip;
    QString d=Helper::getDateTime();
    QString sqltext="insert into users (username,password,salt,regdate,vip,online) values('"+username+"','"+p+"','"+salt+"','"+d+"',"+v+",0)";
    if(!query.exec(sqltext))
        return false;
    QString sqltext2="create table "+username+" (uid integer PRIMARY KEY autoincrement,username varchar(10) UNIQUE,status int)";
    if(!query.exec(sqltext2))
        return false;
    QString sqltext3="create table "+username+"_chat (uid integer PRIMARY KEY autoincrement,fromusername varchar(10),tousername varchar(10),createtime varchar(20),content text)";
    if(!query.exec(sqltext3))
        return false;
    return true;
}
