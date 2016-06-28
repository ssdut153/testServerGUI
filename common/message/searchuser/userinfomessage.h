/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: userinfomessage.h
 *  简要描述:
 *
 *  创建日期: 2016-6-28
 *  作者: 杨志庄
 *  说明:
 *
 *  修改日期:
 *  作者:
 *  说明:
 ****************************************************************************************/
#ifndef USERINFOMESSAGE_H
#define USERINFOMESSAGE_H
#include "../base/feedbackmessage.h"

class userInfoMessage : public feedBackMessage
{
public:
    userInfoMessage();
    userInfoMessage(std::string username,std::string status);
};

#endif // USERINFOMESSAGE_H
