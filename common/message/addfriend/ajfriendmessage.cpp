/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: ajfriendmessage.cpp
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
#include "ajfriendmessage.h"
#include "../../cJSON.h"

ajFriendMessage::ajFriendMessage(std::string fromUserName,std::string toUserName,std::string accept)
{
    fromuser=fromUserName;
    touser=toUserName;
    acpt=accept;
    head="ajFriend";
}
/**
 * @brief ajFriendMessage::ajFriendMessage
 */
ajFriendMessage::ajFriendMessage()
{
    head="ajFriend";
}
/**
 * @brief ajFriendMessage::getJsonString
 * @return  对应的单行Json字符串
 */
std::string ajFriendMessage::getJsonString()
{
    // 创建JSON Object
    cJSON *root = cJSON_CreateObject();
    // 加入节点（键值对）
    cJSON_AddStringToObject(root,"head",head.c_str());
    cJSON_AddStringToObject(root,"fromusername",fromuser.c_str());
    cJSON_AddStringToObject(root,"tousername",touser.c_str());
    cJSON_AddStringToObject(root,"accept",acpt.c_str());
    // 打印JSON数据包
    char *out = cJSON_PrintUnformatted(root);
    // 释放内存
    cJSON_Delete(root);
    std::string temp(out);
    free(out);
    return temp;
}
/**
 * @brief ajFriendMessage::loadfromJson
 * @param textJson Json字符串
 * @return  bool 是否载入成功
 */
bool ajFriendMessage::loadfromJson(std::string textJson)
{
    cJSON *json , *json_fromuser,*json_touser,*json_accept;
    // 解析数据包
    const char* text = textJson.c_str();
    json = cJSON_Parse(text);
    if (!json)
        return false;
    else
    {
        // 解析username
        json_fromuser = cJSON_GetObjectItem( json , "fromusername");
        fromuser=json_fromuser->valuestring;
        json_touser = cJSON_GetObjectItem( json , "tousername");
        touser=json_touser->valuestring;
        json_accept = cJSON_GetObjectItem( json , "accept");
        acpt=json_accept->valuestring;
        // 释放内存空间
        cJSON_Delete(json);
        return true;
    }
}

