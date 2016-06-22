#include "myclient.h"

MyClient::MyClient(std::string user,QTcpSocket *clientConnection,int i)
{
    username=user;
    client=clientConnection;
    index=i;
}
