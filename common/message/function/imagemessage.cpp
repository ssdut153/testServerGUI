#include "imagemessage.h"

imageMessage::imageMessage()
{
    head = "image";
}

imageMessage::imageMessage(QString from, QString to, QString time, QString text)
{
    head = "image";
    FromUserName = from;
    ToUserName = to;
    Content = text;
    CreateTime = time;
}
