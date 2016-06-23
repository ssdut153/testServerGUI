#ifndef REGFEEDBACKMESSAGE_H
#define REGFEEDBACKMESSAGE_H
#include "message.h"

class regFeedBackMessage : public Message
{
public:
    regFeedBackMessage();
    regFeedBackMessage(std::string username,std::string status);
    std::string getJsonString();
    bool loadfromJson(std::string textJson);
    std::string user;
    std::string stat;
};

#endif // REGFEEDBACKMESSAGE_H
