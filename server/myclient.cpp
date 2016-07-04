/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: myclient.cpp
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
#include "myclient.h"
/**
 * @brief MyClient::MyClient
 * @param user 用户名
 * @param clientConnection QTcpSocket*
 * @param i index
 */
MyClient::MyClient(QString user,QTcpSocket *clientConnection,int i)
{
    username=user;
    client=clientConnection;
    index=i;
}
