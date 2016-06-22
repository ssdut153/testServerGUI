#include "helper.h"
#include "md5/md5.h"
#include <time.h>
#include "common/cJSON.h"
unsigned long seed=(unsigned long)time(0);
const char* Helper::hash(const char* text)
{
    MD5 md5;
    md5.update(text);
    return md5.toString().c_str();
}

const char* Helper::tochararray(QString qstr)
{
    std::string str = qstr.toStdString();
    return str.c_str();
}

int Helper::lenofchararrau(const char *text)
{
    int length=0;
    while(text[++length]);
    return length;
}

char* Helper::getsalt(int length)
{
    char* temp=(char*)malloc(sizeof(char)*(length+1));
    for(int i=0;i<length;i++)
        temp[i]=randchar(7);
    temp[length]=0;
    return temp;
}

std::string Helper::getHeadfromJson(std::string textJson)
{
    cJSON *json , *json_head;
    // 解析数据包
    const char* text = textJson.c_str();
    json = cJSON_Parse(text);
    if (!json)
        return "false";
    else
    {
        // 解析head
        json_head = cJSON_GetObjectItem( json , "head");
        std::string head=json_head->valuestring;
        cJSON_Delete(json);
        return head;
    }
}

int Helper::randint(int lower,int higher)
{
    srand(seed);
    seed++;
    return rand()%(higher-lower+1)+lower;
}

char Helper::randchar(int rule)//0-大小写字母、数字、特殊字符；1-大写字母、数字；2-小写字母-数字；3-大小写字母；4-大写字母；5-小写字母；6-数字；7-大小写字母、数字
{
    char j;
    switch(rule)
    {
    case 0:return randint(33,126);
    case 1:
        {
            while(1)
            {
                j=randint(48,90);
                if(('A'<=j && j<='Z') || ('0'<=j && j<='9'))
                    return j;
            }
        }
    case 2:
        {
            while(1)
            {
                j=randint(48,122);
                if(('a'<=j && j<='z') || ('0'<=j && j<='9'))
                    return j;
            }
        }
    case 3:
        {
            while(1)
            {
                j=randint(65,122);
                if(('a'<=j && j<='z') || ('A'<=j && j<='Z'))
                    return j;
            }
        }
    case 4:return randint(65,90);
    case 5:return randint(97,122);
    case 6:return randint(48,57);
    case 7:
        {
            while(1)
            {
                j=randint(48,122);
                if(('a'<=j && j<='z') || ('A'<=j && j<='Z') || ('0'<=j && j<='9'))
                    return j;
            }
        }
    default:return -1;
    }
}
