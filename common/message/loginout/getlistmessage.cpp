#include "getlistmessage.h"

getListMessage::getListMessage()
{
    head = "getList";
}

getListMessage::getListMessage(QString username)
{
    head = "getList";
    user = username;
}
