#ifndef GETLISTMESSAGE_H
#define GETLISTMESSAGE_H

#include "../base/usernamemessage.h"

class getListMessage:public usernameMessage
{
public:
    getListMessage();
    getListMessage(QString username);
};

#endif // GETLISTMESSAGE_H
