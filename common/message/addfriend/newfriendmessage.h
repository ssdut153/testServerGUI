/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: newfriendmessage.h
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
#ifndef NEWFRIENDMESSAGE_H
#define NEWFRIENDMESSAGE_H

#include "../base/usernamemessage.h"

class newFriendMessage : public usernameMessage
{
public:
    newFriendMessage();
    newFriendMessage(QString username, int stat);
    QByteArray getJsonString();
    bool loadfromJson(QByteArray textJson);
    int status;
};

#endif // NEWFRIENDMESSAGE_H
