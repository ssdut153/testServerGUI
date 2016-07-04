/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: myclient.h
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
#ifndef MYCLIENT_H
#define MYCLIENT_H
#include <QtNetwork>
#include<string>
class MyClient
{
public:
    MyClient(QString user,QTcpSocket *clientConnection,int i);
    QTcpSocket* client;
    QString username;
    int index;
};

#endif // MYCLIENT_H
