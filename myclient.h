#ifndef MYCLIENT_H
#define MYCLIENT_H
#include <QtNetwork>
#include<string>
class MyClient
{
public:
    MyClient(std::string user,QTcpSocket *clientConnection,int i);
    QTcpSocket* client;
    std::string username;
    int index;
};

#endif // MYCLIENT_H
