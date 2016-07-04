/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: forcelogoutmessage.h
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
#ifndef FORCELOGOUTMESSAGE_H
#define FORCELOGOUTMESSAGE_H

#include "../base/usernamemessage.h"

class forceLogoutMessage : public usernameMessage
{
public:
    forceLogoutMessage();
    forceLogoutMessage(QString username);
};

#endif // FORCELOGOUTMESSAGE_H
