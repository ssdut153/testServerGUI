/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: searchusermessage.h
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
#ifndef SEARCHUSERMESSAGE_H
#define SEARCHUSERMESSAGE_H

#include "../base/usernamemessage.h"

class searchUserMessage : public usernameMessage
{
public:
    searchUserMessage();
    searchUserMessage(QString username);
};

#endif // SEARCHUSERMESSAGE_H
