#ifndef REGUSERMESSAGE_H
#define REGUSERMESSAGE_H
#include "message.h"

class regUserMessage : public Message
{
public:
    regUserMessage();
    regUserMessage(std::string username,std::string password);
    std::string getJsonString();
    bool loadfromJson(std::string textJson);
    std::string user;
    std::string pass;
};

#endif // REGUSERMESSAGE_H
