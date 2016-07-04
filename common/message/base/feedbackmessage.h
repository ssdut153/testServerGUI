/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: feedbackmessage.h
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
#ifndef FEEDBACKMESSAGE_H
#define FEEDBACKMESSAGE_H

#include "message.h"

class feedBackMessage : public Message
{
public:
    feedBackMessage();
    feedBackMessage(QString username,QString status);
    QByteArray getJsonString();
    bool loadfromJson(QByteArray textJson);
    QString user;
    QString stat;
};

#endif // FEEDBACKMESSAGE_H
