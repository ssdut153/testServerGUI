/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: addfriendmessage.h
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
#ifndef ADDFRIENDMESSAGE_H
#define ADDFRIENDMESSAGE_H
#include "../base/uumessage.h"

class addFriendMessage : public uuMessage
{
public:
    addFriendMessage();
    addFriendMessage(std::string fromUserName,std::string toUserName);
};

#endif // ADDFRIENDMESSAGE_H
