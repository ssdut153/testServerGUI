/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: regfeedbackmessage.cpp
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
#include "regfeedbackmessage.h"
/**
 * @brief regFeedBackMessage::regFeedBackMessage
 * @param username 用户名
 * @param status 状态
 */
regFeedBackMessage::regFeedBackMessage(QString username, QString status)
{
    user=username;
    stat=status;
    head="regFeedBack";
}
/**
 * @brief regFeedBackMessage::regFeedBackMessage
 */
regFeedBackMessage::regFeedBackMessage()
{
    head="regFeedBack";
}
