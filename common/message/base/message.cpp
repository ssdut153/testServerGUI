/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: message.cpp
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
#include "message.h"
/**
 * @brief Message::Message
 */
Message::Message()
{
    head="default";
}
/**
 * @brief Message::Message
 * @param h 头
 */
Message::Message(std::string h)
{
    head=h;
}
/**
 * @brief Message::addHead
 * @param h 头
 */
void Message::addHead(std::string h)
{
    head=h;
}
/**
 * @brief Message::getHead
 * @return 头
 */
std::string Message::getHead()
{
    return head;
}

