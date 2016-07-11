#ifndef FILEMESSAGE_H
#define FILEMESSAGE_H

#include "p2pmessage.h"

class fileMessage:public p2pMessage
{
public:
    fileMessage();
    fileMessage(QString from, QString to, QString time, QString text="");
};

#endif // FILEMESSAGE_H
