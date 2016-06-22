#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>

class Message
{
public:
    Message();
    Message(std::string h);
    virtual ~Message(){}
    virtual std::string getJsonString()=0;
    virtual void loadfromJson()=0;
    void addHead(std::string h);
    std::string getHead();
private:
    std::string head;
};


#endif // MESSAGE_H
