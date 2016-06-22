#ifndef LOGINMESSAGE_H
#define LOGINMESSAGE_H
#include "message.h"

class loginMessage:public Message
{
public:
    loginMessage();
    loginMessage(std::string username,std::string password);
    std::string getJsonString();
    bool loadfromJson(std::string textJson);
    std::string user;
    std::string pass;
};

#endif // LOGINMESSAGE_H
