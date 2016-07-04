/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: forcelogoutmessage.cpp
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
#include "forcelogoutmessage.h"
/**
 * @brief forceLogoutMessage::forceLogoutMessage
 * @param username 用户名
 */
forceLogoutMessage::forceLogoutMessage(QString username)
{
    user=username;
    head="forceLogout";
}
/**
 * @brief forceLogoutMessage::forceLogoutMessage
 */
forceLogoutMessage::forceLogoutMessage()
{
    head="forceLogout";
}
