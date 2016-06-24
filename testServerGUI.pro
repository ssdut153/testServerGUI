#-------------------------------------------------
#
# Project created by QtCreator 2016-06-21T15:39:28
#
#-------------------------------------------------

QT       += core gui
QT += network
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testServerGUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sqlite.cpp \
    helper.cpp \
    md5/md5.cpp \
    common/cJSON.c \
    common/message/base/message.cpp \
    common/user.cpp \
    common/message/loginmessage.cpp \
    common/message/loginfeedbackmessage.cpp \
    common/message/logoutmessage.cpp \
    common/message/getfriendlistmessage.cpp \
    common/message/friendlistmessage.cpp \
    common/message/onlinemessage.cpp \
    common/message/offlinemessage.cpp \
    common/message/addfriendmessage.cpp \
    common/message/newfriendmessage.cpp \
    common/message/requestfriendmessage.cpp \
    common/message/ajfriendmessage.cpp \
    common/message/searchusermessage.cpp \
    common/message/userinfomessage.cpp \
    common/message/p2pmessage.cpp \
    common/message/forcelogoutmessage.cpp \
    common/message/forcereloginmessage.cpp \
    common/message/connecttestmessage.cpp \
    common/message/connectokmessage.cpp \
    myclient.cpp \
    common/message/regusermessage.cpp \
    common/message/regfeedbackmessage.cpp \
    common/message/base/requestmessage.cpp \
    common/message/endsendlistmessage.cpp \
    common/message/startsendlistmessage.cpp \
    common/message/base/usernamemessage.cpp

HEADERS  += mainwindow.h \
    sqlite.h \
    helper.h \
    md5/md5.h \
    common/cJSON.h \
    common/message/base/message.h \
    common/user.h \
    common/message/loginmessage.h \
    common/message/loginfeedbackmessage.h \
    common/message/logoutmessage.h \
    common/message/getfriendlistmessage.h \
    common/message/friendlistmessage.h \
    common/message/onlinemessage.h \
    common/message/offlinemessage.h \
    common/message/addfriendmessage.h \
    common/message/newfriendmessage.h \
    common/message/requestfriendmessage.h \
    common/message/ajfriendmessage.h \
    common/message/searchusermessage.h \
    common/message/userinfomessage.h \
    common/message/p2pmessage.h \
    common/message/forcelogoutmessage.h \
    common/message/forcereloginmessage.h \
    common/message/connecttestmessage.h \
    common/message/connectokmessage.h \
    myclient.h \
    common/allmessage.h \
    common/message/regusermessage.h \
    common/message/regfeedbackmessage.h \
    common/message/base/requestmessage.h \
    common/message/endsendlistmessage.h \
    common/message/startsendlistmessage.h \
    common/message/base/usernamemessage.h

FORMS    += mainwindow.ui
#LIBS += "F:/QtCreate/testServerGUI/MySqlDLL.lib"
