/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: onlinemessage.h
 *  简要描述:
 *
 *  创建日期: 2016-6-28
 *  作者: Yang Zhizhuang
 *  说明:
 *
 *  修改日期:
 *  作者:
 *  说明:
 ****************************************************************************************/
#ifndef ONLINEMESSAGE_H
#define ONLINEMESSAGE_H
#include "../base/usernamemessage.h"

class onlineMessage : public usernameMessage
{
public:
    onlineMessage();
    onlineMessage(QString username);
};

#endif // ONLINEMESSAGE_H
