/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: requestmessage.h
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
#include "requestmessage.h"
#include "../../cJSON.h"
/**
 * @brief requestMessage::requestMessage
 * @param username 用户名
 * @param password 密码
 */
requestMessage::requestMessage()
{
    head="defaultRequest";
}
/**
 * @brief requestMessage::getJsonString
 * @return  对应的单行Json字符串
 */
std::string requestMessage::getJsonString()
{
    // 创建JSON Object
    cJSON *root = cJSON_CreateObject();
    // 加入节点（键值对）
    cJSON_AddStringToObject(root,"head",head.c_str());
    // 打印JSON数据包
    char *out = cJSON_PrintUnformatted(root);
    // 释放内存
    cJSON_Delete(root);
    std::string temp(out);
    free(out);
    return temp;
}
/**
 * @brief requestMessage::loadfromJson
 * @param textJson Json字符串
 * @return  bool 是否载入成功
 */
bool requestMessage::loadfromJson(std::string textJson)
{
    cJSON *json , *json_head;
    // 解析数据包
    const char* text = textJson.c_str();
    json = cJSON_Parse(text);
    if (!json)
        return false;
    else
    {
        // 解析username
        json_head = cJSON_GetObjectItem( json , "head");
        head=json_head->valuestring;
        // 释放内存空间
        cJSON_Delete(json);
        return true;
    }
}
