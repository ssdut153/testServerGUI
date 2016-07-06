#include "offlinep2pmessage.h"

offlineP2PMessage::offlineP2PMessage(QString from, QString to, QString text, QString sendTime)
{
    FromUserName = from;
    ToUserName = to;
    Content = text;
    head = "offlineP2P";
    CreateTime = sendTime;
}

offlineP2PMessage::offlineP2PMessage()
{
    head="offlineP2P";
}
