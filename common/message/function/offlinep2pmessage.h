#ifndef OFFLINEP2PMESSAGE_H
#define OFFLINEP2PMESSAGE_H

#include "p2pmessage.h"

class offlineP2PMessage:public p2pMessage
{
public:
    offlineP2PMessage();
    offlineP2PMessage(QString from, QString to, QString text, QString sendTime);
};

#endif // OFFLINEP2PMESSAGE_H
