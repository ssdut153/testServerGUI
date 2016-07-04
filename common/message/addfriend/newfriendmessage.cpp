/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: newfriendmessage.cpp
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
#include "newfriendmessage.h"

newFriendMessage::newFriendMessage()
{
    head="newFriend";
}

newFriendMessage::newFriendMessage(QString username)
{
    user = username;
    head = "newFriend";
}
