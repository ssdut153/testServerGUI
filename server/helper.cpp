/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: helper.cpp
 *  简要描述:
 *
 *  创建日期: 2016-6-22
 *  作者: Yang Zhizhuang
 *  说明:
 *
 *  修改日期: 2016-6-23
 *  作者: Yang Zhizhuang
 *  说明: 增加getLogFileName函数和log函数以及getLogPath函数
 ****************************************************************************************/
#include "helper.h"
#include "md5/md5.h"
#include <time.h>
#include <QTextStream>
#include <QUuid>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
unsigned long seed=(unsigned long)time(0);
QString Helper::newuuid()
{
    QUuid id=QUuid::createUuid();
    return id.toString();
}

/**
 * @brief Helper::hash
 * @param text 需要hash的文本
 * @return const char* MD5值
 */
QString Helper::hash(QString text)
{
    MD5 md5;
    md5.update(text.toStdString().c_str());
    return QString(md5.toString().c_str());
}
/**
 * @brief Helper::tochararray
 * @param qstr QString
 * @return const char*
 */
const char* Helper::tochararray(QString qstr)
{
    std::string str = qstr.toStdString();
    return str.c_str();
}
/**
 * @brief Helper::getDateTime
 * @return QString yyyy-mm-dd hh:mm:ss
 */
QString Helper::getDateTime()
{
    QString temp;
    struct tm *local;
    time_t t;
    t=time(NULL);
    local=localtime(&t);
    QTextStream(&temp)<<local->tm_year+1900<<"-"<<local->tm_mon+1<<"-"<<local->tm_mday<<" "<<local->tm_hour<<":"<<local->tm_min<<":"<<local->tm_sec;
    return temp;
}
/**
 * @brief Helper::lenofchararrau
 * @param text const char*
 * @return int 字符串长度
 */
int Helper::lenofchararrau(const char *text)
{
    int length=0;
    while(text[++length]);
    return length;
}
/**
 * @brief Helper::getsalt
 * @param length 长度
 * @return char* 对应位数的salt
 */
char* Helper::getsalt(int length)
{
    char* temp=(char*)malloc(sizeof(char)*(length+1));
    for(int i=0;i<length;i++)
        temp[i]=randchar(7);
    temp[length]=0;
    return temp;
}
/**
 * @brief Helper::getHeadfromJson
 * @param textJson std::string Json字符串
 * @return std::string "head"内容
 */
QString Helper::getHeadfromJson(QByteArray textJson)
{
    QJsonParseError jsonParseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(textJson, &jsonParseError);
    if(jsonParseError.error == QJsonParseError::NoError)
    {
        if(jsonDocument.isObject())
        {
            QJsonObject jsonObject = jsonDocument.object();
            if(jsonObject.contains("head"))
            {
                QJsonValue headValue = jsonObject.take("head");
                if(headValue.isString())
                {
                    return headValue.toString();
                }
                else
                {
                    return "false";
                }
            }
            else
            {
                return "false";
            }
        }
        else
        {
            return "false";
        }
    }
    else
    {
        return "false";
    }
}
/**
 * @brief Helper::getLogPath
 * @param logPath 保存用的指针
 */
void Helper::getLogPath(char* logPath)
{
    FILE* fp=fopen("logpath","r");
    if(fp==NULL)
        return;
    fgets(logPath,1024,fp);
    fclose(fp);
}

/**
 * @brief Helper::getLogFileName
 * @param logPath char* 保存的路径
 * @return logPath+yyyy_mm_dd.txt
 */
QString Helper::getLogFileName(QString logPath)
{
    QString temp;
    struct tm *local;
    time_t t;
    t=time(NULL);
    local=localtime(&t);
    QTextStream(&temp)<<logPath<<local->tm_year+1900<<"_"<<local->tm_mon+1<<"_"<<local->tm_mday<<".txt";
    return temp;
}

/**
 * @brief Helper::log
 * @param logText const char* 记录的文本
 * @param logPath char* 保存到的文件绝对路径
 * @return 是否记录成功
 */
bool Helper::log(QString logText, QString logPath)
{
    FILE* fp=fopen(Helper::getLogFileName(logPath).toStdString().c_str(),"at");
    if(fp==NULL)
        return false;
    fputs(logText.toStdString().c_str(),fp);
    fputs("\n",fp);
    fclose(fp);
    return true;
}

/**
 * @brief Helper::randint
 * @param lower 最小值
 * @param higher 最大值
 * @return int 范围内的随机数
 */
int Helper::randint(int lower,int higher)
{
    srand(seed);
    seed++;
    return rand()%(higher-lower+1)+lower;
}
/**
 * @brief Helper::randchar
 * @param rule 0-大小写字母、数字、特殊字符；1-大写字母、数字；2-小写字母-数字；3-大小写字母；4-大写字母；5-小写字母；6-数字；7-大小写字母、数字
 * @return char 随机字符
 */
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
