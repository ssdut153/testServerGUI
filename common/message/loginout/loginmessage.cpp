/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: loginmessage.cpp
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
#include "loginmessage.h"
/**
 * @brief loginMessage::loginMessage
 * @param username 用户名
 * @param password 密码
 */
loginMessage::loginMessage(QString username,QString password)
{
    user = username;
    pass = password;
    head = "login";
}
/**
 * @brief loginMessage::loginMessage
 */
loginMessage::loginMessage()
{
    head = "login";
}
