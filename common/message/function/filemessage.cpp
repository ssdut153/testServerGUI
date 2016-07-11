#include "filemessage.h"

fileMessage::fileMessage()
{
    head = "file";
}

fileMessage::fileMessage(QString from, QString to, QString time, QString text)
{
    head = "file";
    FromUserName = from;
    ToUserName = to;
    Content = text;
    CreateTime = time;
}
