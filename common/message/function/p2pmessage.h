/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: p2pmessage.h
 *  简要描述:
 *
 *  创建日期:
 *  作者:
 *  说明:
 *
 *  修改日期:
 *  作者:
 *  说明:
 ****************************************************************************************/
#ifndef P2PMESSAGE_H
#define P2PMESSAGE_H

#include "../base/message.h"

class p2pMessage : public Message
{
public:
    p2pMessage();
    p2pMessage(QString from, QString to, QString text);
    QByteArray getJsonString();
    bool loadfromJson(QByteArray textJson);
    QString FromUserName;
    QString ToUserName;
    QString CreateTime;
    QString Content;
};

#endif // P2PMESSAGE_H
