/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: friendlistmessage.h
 *  简要描述:
 *
 *  创建日期: 2016-6-24
 *  作者: Yang Zhizhuang
 *  说明:
 *
 *  修改日期:
 *  作者:
 *  说明:
 ****************************************************************************************/
#ifndef FRIENDLISTMESSAGE_H
#define FRIENDLISTMESSAGE_H

#include <QVector>

#include "../base/usernamemessage.h"

class friendListMessage : public Message
{
public:
    friendListMessage();
    void adduser(QString username,int status);
    QByteArray getJsonString();
    bool loadfromJson(QByteArray textJson);
    QVector<QString> user;
    QVector<int> stat;
    int size;
};

#endif // FRIENDLISTMESSAGE_H
