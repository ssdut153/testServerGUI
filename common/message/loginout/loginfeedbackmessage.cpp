/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: loginfeedbackmessage.cpp
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

#include "loginfeedbackmessage.h"
/**
 * @brief loginFeedBackMessage::loginFeedBackMessage
 * @param username 用户名
 * @param status 状态
 */
loginFeedBackMessage::loginFeedBackMessage(QString username, QString status)
{
    user=username;
    stat=status;
    head="loginFeedBack";
}
/**
 * @brief loginFeedBackMessage::loginFeedBackMessage
 */
loginFeedBackMessage::loginFeedBackMessage()
{
    head="loginFeedBack";
}
