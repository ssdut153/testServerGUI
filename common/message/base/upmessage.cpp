/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: upmessage.cpp
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
#include "upmessage.h"
/**
 * @brief upMessage::upMessage
 * @param username 用户名
 * @param password 密码
 */
upMessage::upMessage(QString username, QString password)
{
    user = username;
    pass = password;
    head = "defaulUP";
}
/**
 * @brief upMessage::upMessage
 */
upMessage::upMessage()
{
    head="defaulUP";
}
/**
 * @brief upMessage::getJsonString
 * @return  对应的单行Json字符串
 */
QByteArray upMessage::getJsonString()
{
    QJsonObject jsonObject;
    jsonObject.insert("head", head);
    jsonObject.insert("username", user);
    jsonObject.insert("password", pass);
    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);
    return jsonDocument.toJson(QJsonDocument::Compact);
}
/**
 * @brief upMessage::loadfromJson
 * @param textJson Json字符串
 * @return  bool 是否载入成功
 */
bool upMessage::loadfromJson(QByteArray textJson)
{
    QJsonParseError jsonParseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(textJson, &jsonParseError);
    if(jsonParseError.error == QJsonParseError::NoError)
    {
        if(jsonDocument.isObject())
        {
            QJsonObject jsonObject = jsonDocument.object();
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
            if(jsonObject.contains("password"))
            {
                QJsonValue jsonValue = jsonObject.take("password");
                if(jsonValue.isString())
                {
                    pass = jsonValue.toString();
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

