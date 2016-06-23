/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: loginmessage.h
 *  简要描述:
 *
 *  创建日期: 2016-6-22
 *  作者: Yang Zhizhuang
 *  说明:
 *
 *  修改日期:
 *  作者:
 *  说明:
 ****************************************************************************************/
#ifndef LOGINMESSAGE_H
#define LOGINMESSAGE_H
#include "message.h"

class loginMessage:public Message
{
public:
    loginMessage();
    loginMessage(std::string username,std::string password);
    std::string getJsonString();
    bool loadfromJson(std::string textJson);
    std::string user;
    std::string pass;
};

#endif // LOGINMESSAGE_H
