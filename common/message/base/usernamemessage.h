/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: usernamemessage.h
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
#include "message.h"
#ifndef USERNAMEMESSAGE_H
#define USERNAMEMESSAGE_H


class usernameMessage : public Message
{
public:
    usernameMessage();
    usernameMessage(std::string username);
    std::string getJsonString();
    bool loadfromJson(std::string textJson);
    std::string user;
};

#endif // USERNAMEMESSAGE_H
