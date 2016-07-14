/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: newfriendmessage.cpp
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
#include "newfriendmessage.h"
/**
 * @brief newFriendMessage::newFriendMessage
 */
newFriendMessage::newFriendMessage()
{
    head="newFriend";
}
/**
 * @brief newFriendMessage::newFriendMessage
 * @param username
 * @param stat
 */
newFriendMessage::newFriendMessage(QString username, int stat)
{
    user = username;
    head = "newFriend";
    status = stat;
}
/**
 * @brief newFriendMessage::getJsonString
 * @return  对应的单行Json字符串
 */
QByteArray newFriendMessage::getJsonString()
{
    QJsonObject jsonObject;
    jsonObject.insert("head", head);
    jsonObject.insert("username", user);
    jsonObject.insert("status", status);
    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);
    return jsonDocument.toJson(QJsonDocument::Compact);
}
/**
 * @brief newFriendMessage::loadfromJson
 * @param textJson Json字符串
 * @return  bool 是否载入成功
 */
bool newFriendMessage::loadfromJson(QByteArray textJson)
{
    QJsonParseError jsonParseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(textJson, &jsonParseError);
    if(jsonParseError.error == QJsonParseError::NoError)
    {
        if(jsonDocument.isObject())
        {
            QJsonObject jsonObject  = jsonDocument.object();
            if(jsonObject.contains("username"))
            {
                QJsonValue jsonValue = jsonObject.take("username");
                if(jsonValue.isString())
                {
                    user = jsonValue.toString();
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
            if(jsonObject.contains("status"))
            {
                QJsonValue jsonValue = jsonObject.take("status");
                if(jsonValue.isDouble())
                {
                    status = jsonValue.toInt();
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
