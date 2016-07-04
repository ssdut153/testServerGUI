/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: message.h
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
#ifndef MESSAGE_H
#define MESSAGE_H

#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>

class Message
{
public:
    Message();
    Message(QString h);
    virtual ~Message();
    virtual QByteArray getJsonString() = 0;
    virtual bool loadfromJson(QByteArray textJson) = 0;
    void addHead(QString h);
    QString getHead();
    QString head;
};


#endif // MESSAGE_H
