/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: friendlistmessage.cpp
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
#include "friendlistmessage.h"
/**
 * @brief friendListMessage::friendListMessage
 * @param username 用户名
 */
void friendListMessage::adduser(QString username, int status)
{
    user.push_back(username);
    stat.push_back(status);
    size++;
}
/**
 * @brief friendListMessage::friendListMessage
 */
friendListMessage::friendListMessage()
{
    head = "friendList";
    size = 0;
}
/**
 * @brief friendListMessage::getJsonString
 * @return
 */
QByteArray friendListMessage::getJsonString()
{
    QJsonArray jsonArray;
    for(int i = 0;i < size;i++)
    {
        QJsonObject jsonObject;
        jsonObject.insert("username", user[i]);
        jsonObject.insert("status", stat[i]);
        jsonArray.push_back(jsonObject);
        QJsonDocument tempJsonDocument;
        tempJsonDocument.setObject(jsonObject);
        jsonArray.push_back(QString(tempJsonDocument.toJson(QJsonDocument::Compact)));
    }
    QJsonDocument jsonDocument;
    jsonDocument.setArray(jsonArray);
    return jsonDocument.toJson(QJsonDocument::Compact);
}
/**
 * @brief friendListMessage::loadfromJson
 * @param textJson
 * @return
 */
bool friendListMessage::loadfromJson(QByteArray textJson)
{
    QJsonParseError jsonParseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(textJson, &jsonParseError);
    if(jsonParseError.error == QJsonParseError::NoError)
    {
        if(jsonDocument.isArray())
        {
            QJsonArray jsonArray = jsonDocument.array();
            size = jsonArray.size();
            for(int i = 0;i < size;i++)
            {
                QJsonValue jsonValue = jsonArray.at(i);
                if(jsonValue.isObject())
                {
                    QJsonObject tempJsonObject =jsonValue.toObject();
                    if(tempJsonObject.contains("username"))
                    {
                        QJsonValue jsonValue = tempJsonObject.take("username");
                        if(jsonValue.isString())
                        {
                            user.push_back(jsonValue.toString());
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
                    if(tempJsonObject.contains("status"))
                    {
                        QJsonValue jsonValue = tempJsonObject.take("status");
                        if(jsonValue.isDouble())
                        {
                            stat.push_back(jsonValue.toInt());
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
