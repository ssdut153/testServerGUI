/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: regusermessage.h
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
#ifndef REGUSERMESSAGE_H
#define REGUSERMESSAGE_H
#include "message.h"

class regUserMessage : public Message
{
public:
    regUserMessage();
    regUserMessage(std::string username,std::string password);
    std::string getJsonString();
    bool loadfromJson(std::string textJson);
    std::string user;
    std::string pass;
};

#endif // REGUSERMESSAGE_H
