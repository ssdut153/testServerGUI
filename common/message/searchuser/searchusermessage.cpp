/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: searchusermessage.cpp
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
#include "searchusermessage.h"

searchUserMessage::searchUserMessage()
{
    head="searchUser";
}

searchUserMessage::searchUserMessage(QString username)
{
    user=username;
    head="searchUser";
}
