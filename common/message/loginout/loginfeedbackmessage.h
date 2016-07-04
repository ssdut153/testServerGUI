/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: loginfeedbackmessage.h
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
#ifndef LOGINFEEDBACKMESSAGE_H
#define LOGINFEEDBACKMESSAGE_H
#include "../base/feedbackmessage.h"

class loginFeedBackMessage : public feedBackMessage
{
public:
    loginFeedBackMessage();
    loginFeedBackMessage(QString username, QString status);
};

#endif // LOGINFEEDBACKMESSAGE_H
