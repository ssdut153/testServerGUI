/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: p2pmessage.h
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
#ifndef P2PMESSAGE_H
#define P2PMESSAGE_H
#include "../base/message.h"

class p2pMessage : public Message
{
public:
    p2pMessage();
    p2pMessage(std::string from,std::string to,std::string text);
    std::string getJsonString();
    bool loadfromJson(std::string textJson);
    std::string FromUserName;
    std::string ToUserName;
    std::string CreateTime;
    std::string Content;
};

#endif // P2PMESSAGE_H
