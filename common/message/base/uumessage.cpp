/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: uumessage.cpp
 *  简要描述:
 *
 *  创建日期: 2016-6-28
 *  作者: Yang Zhizhuang
 *  说明:
 *
 *  修改日期:
 *  作者:
 *  说明:
 ****************************************************************************************/
#include "uumessage.h"
#include "../../cJSON.h"

uuMessage::uuMessage(std::string fromUserName,std::string toUserName)
{
    fromuser=fromUserName;
    touser=toUserName;
    head="defaultUu";
}
/**
 * @brief uuMessage::uuMessage
 */
uuMessage::uuMessage()
{
    head="defaultUu";
}
/**
 * @brief uuMessage::getJsonString
 * @return  对应的单行Json字符串
 */
std::string uuMessage::getJsonString()
{
    // 创建JSON Object
    cJSON *root = cJSON_CreateObject();
    // 加入节点（键值对）
    cJSON_AddStringToObject(root,"head",head.c_str());
    cJSON_AddStringToObject(root,"fromusername",fromuser.c_str());
    cJSON_AddStringToObject(root,"tousername",touser.c_str());
    // 打印JSON数据包
    char *out = cJSON_PrintUnformatted(root);
    // 释放内存
    cJSON_Delete(root);
    std::string temp(out);
    free(out);
    return temp;
}
/**
 * @brief uuMessage::loadfromJson
 * @param textJson Json字符串
 * @return  bool 是否载入成功
 */
bool uuMessage::loadfromJson(std::string textJson)
{
    cJSON *json , *json_fromuser,*json_touser;
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
        // 释放内存空间
        cJSON_Delete(json);
        return true;
    }
}
