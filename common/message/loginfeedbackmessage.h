#ifndef LOGINFEEDBACKMESSAGE_H
#define LOGINFEEDBACKMESSAGE_H
#include "message.h"

class loginFeedBackMessage : public Message
{
public:
    loginFeedBackMessage();
    loginFeedBackMessage(std::string username,std::string status);
    std::string getJsonString();
    bool loadfromJson(std::string textJson);
    std::string user;
    std::string stat;
};

#endif // LOGINFEEDBACKMESSAGE_H
