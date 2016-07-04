/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: userinfomessage.cpp
 *  简要描述:
 *
 *  创建日期: 2016-6-28
 *  作者: 杨志庄
 *  说明:
 *
 *  修改日期:
 *  作者:
 *  说明:
 ****************************************************************************************/
#include "userinfomessage.h"

userInfoMessage::userInfoMessage()
{
    head="userInfo";
}

userInfoMessage::userInfoMessage(QString username, QString status)
{
    user=username;
    stat=status;
    head="userInfo";
}
