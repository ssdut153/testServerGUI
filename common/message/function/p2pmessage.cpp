/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: p2pmessage.cpp
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
#include "p2pmessage.h"
#include <time.h>
#include <QString>
#include <QTextStream>
#include "../../cJSON.h"
/**
 * @brief p2pMessage::p2pMessage
 * @param username 用户名
 * @param status 状态
 */
p2pMessage::p2pMessage(std::string from,std::string to,std::string text)
{
    FromUserName=from;
    ToUserName=to;
    Content=text;
    head="p2p";
    QString temp;
    struct tm *local;
    time_t t;
    t=time(NULL);
    local=localtime(&t);
    QTextStream(&temp)<<local->tm_year+1900<<"-"<<local->tm_mon+1<<"-"<<local->tm_mday<<" "<<local->tm_hour<<":"<<local->tm_min<<":"<<local->tm_sec;
    CreateTime=temp.toStdString();
}
/**
 * @brief p2pMessage::p2pMessage
 */
p2pMessage::p2pMessage()
{
    head="defaultP2P";
}
/**
 * @brief p2pMessage::getJsonString
 * @return std::string 对应的单行Json字符串
 */
std::string p2pMessage::getJsonString()
{
    // 创建JSON Object
    cJSON *root = cJSON_CreateObject();
    // 加入节点（键值对）
    cJSON_AddStringToObject(root,"head",head.c_str());
    cJSON_AddStringToObject(root,"fromusername",FromUserName.c_str());
    cJSON_AddStringToObject(root,"tousername",ToUserName.c_str());
    cJSON_AddStringToObject(root,"createtime",CreateTime.c_str());
    cJSON_AddStringToObject(root,"content",Content.c_str());
    // 打印JSON数据包
    char *out = cJSON_PrintUnformatted(root);
    // 释放内存
    cJSON_Delete(root);
    std::string temp(out);
    free(out);
    return temp;
}
/**
 * @brief p2pMessage::loadfromJson
 * @param textJson Json字符串
 * @return bool 是否载入成功
 */
bool p2pMessage::loadfromJson(std::string textJson)
{
    cJSON *json , *json_from , *json_to,*json_time,*json_content;
    // 解析数据包
    const char* text = textJson.c_str();
    json = cJSON_Parse(text);
    if (!json)
        return false;
    else
    {
        head="p2p";
        json_from = cJSON_GetObjectItem( json , "fromusername");
        FromUserName=json_from->valuestring;
        json_to = cJSON_GetObjectItem( json , "tousername");
        ToUserName=json_to->valuestring;
        json_time = cJSON_GetObjectItem( json , "createtime");
        CreateTime=json_time->valuestring;
        json_content = cJSON_GetObjectItem( json , "content");
        Content=json_content->valuestring;
        // 释放内存空间
        cJSON_Delete(json);
        return true;
    }

}
