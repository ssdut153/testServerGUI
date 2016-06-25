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
#include "../../cJSON.h"
/**
 * @brief friendListMessage::friendListMessage
 * @param username 用户名
 */
void friendListMessage::adduser(std::string username)
{
    user.push_back(username);
    size++;
}
/**
 * @brief friendListMessage::friendListMessage
 */
friendListMessage::friendListMessage()
{
    head="friendList";
    size=0;
}
/**
 * @brief friendListMessage::getJsonString
 * @return
 */
std::string friendListMessage::getJsonString()
{
    cJSON *root, **dir;
    char *out;
    dir = (cJSON**)malloc(sizeof(cJSON*)*size);
    //创建json数组型结构体
    root = cJSON_CreateArray();
    for (int i = 0; i < size; i++)
    {
        //创建对象至数组
        cJSON_AddItemToArray(root, dir[i] = cJSON_CreateObject());
        //为对象添加字符串键值对
        cJSON_AddStringToObject(dir[i], "username", user[i].c_str());
    }
    //将json结构体转换为字符串
    out = cJSON_PrintUnformatted(root);
    std::string temp(out);
    //释放内存
    free(out);
    cJSON_Delete(root);
    return temp;
}
/**
 * @brief friendListMessage::loadfromJson
 * @param textJson
 * @return
 */
bool friendListMessage::loadfromJson(std::string textJson)
{
    cJSON * root = NULL, *item = NULL, *username;
    char *pr = NULL;
    if ((root = cJSON_Parse(textJson.c_str())) == NULL)
        return false;
    int iSize = cJSON_GetArraySize(root);
    size = iSize;
    for (int iCnt = 0; iCnt < iSize; iCnt++)
    {
        cJSON * pSub = cJSON_GetArrayItem(root, iCnt);
        pr = cJSON_Print(pSub);
        item = cJSON_Parse(pr);
        if (NULL == pSub)
            continue;
        //将键值item从json节点中取出
        username = cJSON_GetObjectItem(item, "username");
        //加入到题库结构体数组
        std::string temp(username->valuestring);
        user.push_back(temp);
    }
    cJSON_Delete(root);
    return true;
}