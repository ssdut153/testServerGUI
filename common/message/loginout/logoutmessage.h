/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: logoutmessage.h
 *  简要描述:
 *
 *  创建日期: 2016-6-23
 *  作者: Yang Zhizhuang
 *  说明:
 *
 *  修改日期:
 *  作者:
 *  说明:
 ****************************************************************************************/
#ifndef LOGOUTMESSAGE_H
#define LOGOUTMESSAGE_H

#include "common/message/base/usernamemessage.h"

class logoutMessage : public usernameMessage
{
public:
    logoutMessage();
    logoutMessage(QString username);
};

#endif // LOGOUTMESSAGE_H
