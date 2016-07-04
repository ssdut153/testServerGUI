/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: logoutmessage.cpp
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
#include "logoutmessage.h"
/**
 * @brief logoutMessage::logoutMessage
 * @param username 用户名
 */
logoutMessage::logoutMessage(QString username)
{
    user = username;
    head = "logout";
}
/**
 * @brief logoutMessage::logoutMessage
 */
logoutMessage::logoutMessage()
{
    head = "logout";
}
