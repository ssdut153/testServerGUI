/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: uumessage.cpp
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
#include "uumessage.h"

uuMessage::uuMessage(QString fromUserName, QString toUserName)
{
    fromuser = fromUserName;
    touser = toUserName;
    head = "defaultUu";
}
/**
 * @brief uuMessage::uuMessage
 */
uuMessage::uuMessage()
{
    head = "defaultUu";
}
/**
 * @brief uuMessage::getJsonString
 * @return  对应的单行Json字符串
 */
QByteArray uuMessage::getJsonString()
{
    QJsonObject jsonObject;
    jsonObject.insert("head", head);
    jsonObject.insert("fromusername", fromuser);
    jsonObject.insert("tousername", touser);
    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);
    return jsonDocument.toJson(QJsonDocument::Compact);
}
/**
 * @brief uuMessage::loadfromJson
 * @param textJson Json字符串
 * @return  bool 是否载入成功
 */
bool uuMessage::loadfromJson(QByteArray textJson)
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
