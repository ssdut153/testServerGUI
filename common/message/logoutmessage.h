#ifndef LOGOUTMESSAGE_H
#define LOGOUTMESSAGE_H
#include "message.h"

class logoutMessage : public Message
{
public:
    logoutMessage();
    logoutMessage(std::string username);
    std::string getJsonString();
    bool loadfromJson(std::string textJson);
    std::string user;
};

#endif // LOGOUTMESSAGE_H
