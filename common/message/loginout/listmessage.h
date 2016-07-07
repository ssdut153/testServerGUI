#ifndef LISTMESSAGE_H
#define LISTMESSAGE_H

#include <QMap>
#include <QVector>
#include "../base/message.h"

class listMessage:public Message
{
public:
    listMessage();
    listMessage(QString username);
    void addFriendRequestMessage(QString from);
    void addOfflineMessage(QString from, QString createTime, QString content);
    QByteArray getJsonString();
    bool loadfromJson(QByteArray textJson);
    QString user;
    QVector<QString> requestUsers;
    QVector<QString> messageFromUsers;
    QVector<QString> createTime;
    QVector<QString> contents;

};

#endif // LISTMESSAGE_H
