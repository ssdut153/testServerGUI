/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: ajfriendmessage.cpp
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
#include "ajfriendmessage.h"

ajFriendMessage::ajFriendMessage(QString fromUserName, QString toUserName, QString accept)
{
    fromuser = fromUserName;
    touser = toUserName;
    acpt = accept;
    head = "ajFriend";
}
/**
 * @brief ajFriendMessage::ajFriendMessage
 */
ajFriendMessage::ajFriendMessage()
{
    head = "ajFriend";
}
/**
 * @brief ajFriendMessage::getJsonString
 * @return  对应的单行Json字符串
 */
QByteArray ajFriendMessage::getJsonString()
{
    QJsonObject jsonObject;
    jsonObject.insert("head", head);
    jsonObject.insert("fromusername", fromuser);
    jsonObject.insert("tousername", touser);
    jsonObject.insert("accept", acpt);
    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);
    return jsonDocument.toJson(QJsonDocument::Compact);
}
/**
 * @brief ajFriendMessage::loadfromJson
 * @param textJson Json字符串
 * @return  bool 是否载入成功
 */
bool ajFriendMessage::loadfromJson(QByteArray textJson)
{
    QJsonParseError jsonParseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(textJson, &jsonParseError);
    if(jsonParseError.error == QJsonParseError::NoError)
    {
        if(jsonDocument.isObject())
        {
            QJsonObject jsonObject = jsonDocument.object();
            if(jsonObject.contains("fromusername"))
            {
                QJsonValue jsonValue = jsonObject.take("fromusername");
                if(jsonValue.isString())
                {
                    fromuser = jsonValue.toString();
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
                    touser = jsonValue.toString();
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
            if(jsonObject.contains("accept"))
            {
                QJsonValue jsonValue = jsonObject.take("accept");
                if(jsonValue.isString())
                {
                    acpt = jsonValue.toString();
                }
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

