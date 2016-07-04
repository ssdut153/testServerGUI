/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: getfriendlistmessage.h
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
#ifndef GETFRIENDLISTMESSAGE_H
#define GETFRIENDLISTMESSAGE_H

#include "../base/usernamemessage.h"

class getFriendListMessage : public usernameMessage
{
public:
    getFriendListMessage();
    getFriendListMessage(QString username);
};

#endif // GETFRIENDLISTMESSAGE_H
