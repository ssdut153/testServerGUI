/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: usernamemessage.h
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
#ifndef USERNAMEMESSAGE_H
#define USERNAMEMESSAGE_H

#include "message.h"

class usernameMessage : public Message
{
public:
    usernameMessage();
    usernameMessage(QString username);
    QByteArray getJsonString();
    bool loadfromJson(QByteArray textJson);
    QString user;
};

#endif // USERNAMEMESSAGE_H
