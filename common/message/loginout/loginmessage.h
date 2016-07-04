/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: loginmessage.h
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
#ifndef LOGINMESSAGE_H
#define LOGINMESSAGE_H

#include "common/message/base/upmessage.h"

class loginMessage:public upMessage
{
public:
    loginMessage();
    loginMessage(QString username,QString password);
};

#endif // LOGINMESSAGE_H
