/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: upmessage.h
 *  简要描述:
 *
 *  创建日期: 2016-6-25
 *  作者: Yang Zhizhuang
 *  说明:
 *
 *  修改日期:
 *  作者:
 *  说明:
 ****************************************************************************************/
#ifndef UPMESSAGE_H
#define UPMESSAGE_H

#include "message.h"

class upMessage : public Message
{
public:
    upMessage();
    upMessage(QString username,QString password);
    QByteArray getJsonString();
    bool loadfromJson(QByteArray textJson);
    QString user;
    QString pass;
};

#endif // UPMESSAGE_H
