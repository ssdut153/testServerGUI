/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: usernamemessage.cpp
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
#include "usernamemessage.h"
#include "../../cJSON.h"
/**
 * @brief usernameMessage::usernameMessage
 * @param username 用户名
 */
usernameMessage::usernameMessage(std::string username)
{
    user=username;
    head="defaultUsername";
}
/**
 * @brief usernameMessage::usernameMessage
 */
usernameMessage::usernameMessage()
{
    head="defaultUsername";
}
/**
 * @brief usernameMessage::getJsonString
 * @return  对应的单行Json字符串
 */
std::string usernameMessage::getJsonString()
{
    // 创建JSON Object
    cJSON *root = cJSON_CreateObject();
    // 加入节点（键值对）
    cJSON_AddStringToObject(root,"head",head.c_str());
    cJSON_AddStringToObject(root,"username",user.c_str());
    // 打印JSON数据包
    char *out = cJSON_PrintUnformatted(root);
    // 释放内存
    cJSON_Delete(root);
    std::string temp(out);
    free(out);
    return temp;
}
/**
 * @brief usernameMessage::loadfromJson
 * @param textJson Json字符串
 * @return  bool 是否载入成功
 */
bool usernameMessage::loadfromJson(std::string textJson)
{
    cJSON *json , *json_username;
    // 解析数据包
    const char* text = textJson.c_str();
    json = cJSON_Parse(text);
    if (!json)
        return false;
    else
    {
        // 解析username
        json_username = cJSON_GetObjectItem( json , "username");
        user=json_username->valuestring;
        // 释放内存空间
        cJSON_Delete(json);
        return true;
    }
}

