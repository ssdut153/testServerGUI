/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: friendlistmessage.cpp
 *  简要描述:
 *
 *  创建日期: 2016-6-24
 *  作者: Yang Zhizhuang
 *  说明:
 *
 *  修改日期:
 *  作者:
 *  说明:
 ****************************************************************************************/
#include "friendlistmessage.h"
#include "../cJSON.h"
/**
 * @brief friendListMessage::friendListMessage
 * @param username 用户名
 */
friendListMessage::friendListMessage(std::string username)
{
    user=username;
    head="friendList";
}
/**
 * @brief friendListMessage::friendListMessage
 */
friendListMessage::friendListMessage()
{
    head="friendList";
}
