#ifndef HELPER_H
#define HELPER_H
#include<iostream>
#include<QString>
class Helper
{
public:
    static const char* hash(const char* text);
    static const char* tochararray(QString qstr);
    static char randchar(int rule);
    static int randint(int lower,int higher);
    static char* getsalt(int length=8);
    static int lenofchararrau(char* text);
};

#endif // HELPER_H
