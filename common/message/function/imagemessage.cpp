#include "imagemessage.h"

imageMessage::imageMessage()
{
    head = "image";
}

imageMessage::imageMessage(QString from, QString to, QString text)
{
    head = "image";
    FromUserName = from;
    ToUserName = to;
    Content = text;
    CreateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
}
