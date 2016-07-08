#include "p2pmessage.h"

p2pMessage::p2pMessage(QString from, QString to, QString time, QString text)
{
    FromUserName = from;
    ToUserName = to;
    Content = text;
    head = "p2p";
    CreateTime = time;
}

p2pMessage::p2pMessage()
{
    head="defaultP2P";
}

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
