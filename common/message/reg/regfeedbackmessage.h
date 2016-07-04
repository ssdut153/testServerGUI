/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: regfeedbackmessage.h
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
#ifndef REGFEEDBACKMESSAGE_H
#define REGFEEDBACKMESSAGE_H

#include "../base/feedbackmessage.h"

class regFeedBackMessage : public feedBackMessage
{
public:
    regFeedBackMessage();
    regFeedBackMessage(QString username, QString status);
};

#endif // REGFEEDBACKMESSAGE_H
