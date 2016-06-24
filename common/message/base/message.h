/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: message.h
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
#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>

class Message
{
public:
    Message();
    Message(std::string h);
    virtual ~Message(){}
    virtual std::string getJsonString()=0;
    virtual bool loadfromJson(std::string textJson)=0;
    void addHead(std::string h);
    std::string getHead();
    std::string head;
};


#endif // MESSAGE_H
