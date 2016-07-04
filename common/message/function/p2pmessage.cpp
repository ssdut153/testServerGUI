/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: p2pmessage.cpp
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
#include "p2pmessage.h"
#include <QDateTime>
/**
 * @brief p2pMessage::p2pMessage
 * @param username 用户名
 * @param status 状态
 */
p2pMessage::p2pMessage(QString from, QString to, QString text)
{
    FromUserName = from;
    ToUserName = to;
    Content = text;
    head = "p2p";
    CreateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
}
/**
 * @brief p2pMessage::p2pMessage
 */
p2pMessage::p2pMessage()
{
    head="defaultP2P";
}
/**
 * @brief p2pMessage::getJsonString
 * @return QString 对应的单行Json字符串
 */
QByteArray p2pMessage::getJsonString()
{
    QJsonObject jsonObject;
    jsonObject.insert("head", head);
    jsonObject.insert("fromusername", FromUserName);
    jsonObject.insert("tousername", ToUserName);
    jsonObject.insert("createtime", CreateTime);
    jsonObject.insert("content", Content);
    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);
    return jsonDocument.toJson(QJsonDocument::Compact);
}
/**
 * @brief p2pMessage::loadfromJson
 * @param textJson Json字符串
 * @return bool 是否载入成功
 */
bool p2pMessage::loadfromJson(QByteArray textJson)
{
    QJsonParseError jsonParseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(textJson, &jsonParseError);
    if(jsonParseError.error == jsonParseError.NoError)
    {
        if(jsonDocument.isObject())
        {
            QJsonObject jsonObject = jsonDocument.object();
            if(jsonObject.contains("fromusername"))
            {
                QJsonValue jsonValue = jsonObject.take("fromusername");
                if(jsonValue.isString())
                {
                    FromUserName = jsonValue.toString();
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
            if(jsonObject.contains("tousername"))
            {
                QJsonValue jsonValue = jsonObject.take("tousername");
                if(jsonValue.isString())
                {
                    ToUserName = jsonValue.toString();
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
            if(jsonObject.contains("createtime"))
            {
                QJsonValue jsonValue = jsonObject.take("createtime");
                if(jsonValue.isString())
                {
                    CreateTime = jsonValue.toString();
                }
                else
                {
                    return false;
                }
            }
            if(jsonObject.contains("content"))
            {
                QJsonValue jsonValue = jsonObject.take("content");
                if(jsonValue.isString())
                {
                    Content = jsonValue.toString();
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
    return true;
}
