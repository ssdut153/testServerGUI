/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: regusermessage.cpp
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
#include "regusermessage.h"
#include "../../cJSON.h"
/**
 * @brief regUserMessage::regUserMessage
 * @param username 用户名
 * @param password 密码
 */
regUserMessage::regUserMessage(std::string username,std::string password)
{
    user=username;
    pass=password;
    head="regUser";
}
/**
 * @brief regUserMessage::regUserMessage
 */
regUserMessage::regUserMessage()
{
    head="regUser";
}
