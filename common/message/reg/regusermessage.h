/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: regusermessage.h
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
#ifndef REGUSERMESSAGE_H
#define REGUSERMESSAGE_H

#include "common/message/base/upmessage.h"

class regUserMessage : public upMessage
{
public:
    regUserMessage();
    regUserMessage(QString username, QString password);
};

#endif // REGUSERMESSAGE_H
