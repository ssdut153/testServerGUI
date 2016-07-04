/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: uumessage.h
 *  简要描述:
 *
 *  创建日期: 2016-6-28
 *  作者: Yang Zhizhuang
 *  说明:
 *
 *  修改日期:
 *  作者:
 *  说明:
 ****************************************************************************************/
#ifndef UUMESSAGE_H
#define UUMESSAGE_H

#include "message.h"

class uuMessage : public Message
{
public:
    uuMessage();
    uuMessage(QString fromUserName,QString toUserName);
    QByteArray getJsonString();
    bool loadfromJson(QByteArray textJson);
    QString fromuser;
    QString touser;
};

#endif // UUMESSAGE_H
