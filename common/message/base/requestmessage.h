/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: requestmessage.h
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
#ifndef REQUESTMESSAGE_H
#define REQUESTMESSAGE_H
#include "message.h"

class requestMessage : public Message
{
public:
    requestMessage();
    QByteArray getJsonString();
    bool loadfromJson(QByteArray textJson);

};

#endif // REQUESTMESSAGE_H
