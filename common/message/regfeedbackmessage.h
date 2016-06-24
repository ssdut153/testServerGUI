/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: regfeedbackmessage.h
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
#ifndef REGFEEDBACKMESSAGE_H
#define REGFEEDBACKMESSAGE_H
#include "./base/message.h"

class regFeedBackMessage : public Message
{
public:
    regFeedBackMessage();
    regFeedBackMessage(std::string username,std::string status);
    std::string getJsonString();
    bool loadfromJson(std::string textJson);
    std::string user;
    std::string stat;
};

#endif // REGFEEDBACKMESSAGE_H
