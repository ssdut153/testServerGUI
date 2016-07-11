#include "listmessage.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>

listMessage::listMessage(QString username)
{
    head = "listmessage";
    this->user = username;
}

listMessage::listMessage()
{

}

void listMessage::addFriendRequestMessage(QString from)
{
    this->requestUsers.push_back(from);
}

void listMessage::addOfflineMessage(QString from, QString createTime, QString content)
{
    this->messageFromUsers.push_back(from);
    this->createTime.push_back(createTime);
    this->contents.push_back(content);
}

QByteArray listMessage::getJsonString()
{
    QJsonObject jsonObject;

    jsonObject.insert("head", "listmessage");
    jsonObject.insert("tousername", this->user);

    QJsonArray requestJsonArray;
    int size1 = this->requestUsers.size();
    for(int i = 0; i < size1; i++)
    {
        requestJsonArray.push_back(this->requestUsers[i]);
    }
    jsonObject.insert("offlinerequest", requestJsonArray);

    QJsonArray offlineJsonArray;
    int size2 = this->messageFromUsers.size();
    for(int i = 0; i <size2; i++)
    {
        QJsonObject tempJsonObject;
        tempJsonObject.insert("fromusername", this->messageFromUsers[i]);
        tempJsonObject.insert("createtime", this->createTime[i]);
        tempJsonObject.insert("content", this->contents[i]);
        offlineJsonArray.push_back(tempJsonObject);
    }
    jsonObject.insert("offlinechat", offlineJsonArray);

    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);
    return jsonDocument.toJson(QJsonDocument::Compact);
}

bool listMessage::loadfromJson(QByteArray textJson)
{
    QJsonParseError jsonParseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(textJson, &jsonParseError);
    if(jsonParseError.error == QJsonParseError::NoError)
    {
        if(jsonDocument.isObject())
        {
            QJsonObject jsonObject = jsonDocument.object();
            if(jsonObject.contains("offlinerequest"))
            {
                QJsonValue jsonValue = jsonObject.take("offlinerequest");
                if(jsonValue.isArray())
                {
                    QJsonArray jsonArray = jsonValue.toArray();
                    int size = jsonArray.size();
                    for(int i = 0; i < size; i++)
                    {
                        QJsonValue tempValue = jsonArray.at(i);
                        if(tempValue.isString())
                        {
                            QString tempString = tempValue.toString();
                            this->requestUsers.push_back(tempString);
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
            if(jsonObject.contains("offlinechat"))
            {
                QJsonValue tempJsonValue = jsonObject.take("offlinechat");
                if(tempJsonValue.isArray())
                {
                    QJsonArray tempJsonArray = tempJsonValue.toArray();
                    int size = tempJsonArray.size();
                    for(int i = 0; i < size; i++)
                    {
                        QJsonValue tempJsonValue2 = tempJsonArray.at(i);
                        if(tempJsonValue2.isObject())
                        {
                            QJsonObject tempJsonObject = tempJsonValue2.toObject();
                            if(tempJsonObject.contains("fromusername"))
                            {
                                QJsonValue tempJsonValue3 = tempJsonObject.take("fromusername");
                                if(tempJsonValue3.isString())
                                {
                                    this->messageFromUsers.push_back(tempJsonValue3.toString());
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
                            if(tempJsonObject.contains("createtime"))
                            {
                                QJsonValue tempJsonValue3 = tempJsonObject.take("createtime");
                                if(tempJsonValue3.isString())
                                {
                                    this->createTime.push_back(tempJsonValue3.toString());
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
                            if(tempJsonObject.contains("content"))
                            {
                                QJsonValue tempJsonValue3 = tempJsonObject.take("content");
                                if(tempJsonValue3.isString())
                                {
                                    this->contents.push_back(tempJsonValue3.toString());
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
