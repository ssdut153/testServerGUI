#ifndef IMAGEMESSAGE_H
#define IMAGEMESSAGE_H

#include "p2pmessage.h"

class imageMessage:public p2pMessage
{
public:
    imageMessage();
    imageMessage(QString from, QString to, QString time, QString text = "");
};

#endif // IMAGEMESSAGE_H
