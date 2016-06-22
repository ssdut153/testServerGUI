#include "message.h"

Message::Message()
{
    head="";
}

Message::Message(std::string h)
{
    head=h;
}
void Message::addHead(std::string h)
{
    head=h;
}
std::string Message::getHead()
{
    return head;
}

