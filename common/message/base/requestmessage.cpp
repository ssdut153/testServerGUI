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
#include "requestmessage.h"

/**
 * @brief requestMessage::requestMessage
 */
requestMessage::requestMessage()
{
    head="defaultRequest";
}
/**
 * @brief requestMessage::getJsonString
 * @return  对应的单行Json字符串
 */
QByteArray requestMessage::getJsonString()
{
    QJsonObject jsonObject;
    jsonObject.insert("head", head);
    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);
    return jsonDocument.toJson(QJsonDocument::Compact);
}
/**
 * @brief requestMessage::loadfromJson
 * @param textJson Json字符串
 * @return  bool 是否载入成功
 */
bool requestMessage::loadfromJson(QByteArray textJson)
{
    QJsonParseError jsonParseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(textJson, &jsonParseError);
    if(jsonParseError.error == QJsonParseError::NoError)
    {
        if(jsonDocument.isObject())
        {
            QJsonObject jsonObject = jsonDocument.object();
            if(jsonObject.contains("head"))
            {
                QJsonValue headValue = jsonObject.take("head");
                if(headValue.isString())
                {
                    head = headValue.toString();
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
