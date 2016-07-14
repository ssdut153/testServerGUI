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
        window/mainwindow.cpp \
    server/sqlite.cpp \
    server/helper.cpp \
    server/md5/md5.cpp \
    common/message/base/message.cpp \
    common/user.cpp \
    common/message/loginout/loginmessage.cpp \
    common/message/loginout/loginfeedbackmessage.cpp \
    common/message/loginout/logoutmessage.cpp \
    common/message/friendlist/getfriendlistmessage.cpp \
    common/message/friendlist/friendlistmessage.cpp \
    common/message/loginout/onlinemessage.cpp \
    common/message/loginout/offlinemessage.cpp \
    common/message/addfriend/addfriendmessage.cpp \
    common/message/addfriend/newfriendmessage.cpp \
    common/message/addfriend/requestfriendmessage.cpp \
    common/message/addfriend/ajfriendmessage.cpp \
    common/message/searchuser/searchusermessage.cpp \
    common/message/searchuser/userinfomessage.cpp \
    common/message/function/p2pmessage.cpp \
    common/message/function/forcelogoutmessage.cpp \
    common/message/function/forcereloginmessage.cpp \
    common/message/function/connecttestmessage.cpp \
    common/message/function/connectokmessage.cpp \
    server/myclient.cpp \
    common/message/reg/regusermessage.cpp \
    common/message/reg/regfeedbackmessage.cpp \
    common/message/base/requestmessage.cpp \
    common/message/base/usernamemessage.cpp \
    common/message/base/upmessage.cpp \
    common/message/base/feedbackmessage.cpp \
    common/message/base/uumessage.cpp \
    common/message/loginout/listmessage.cpp \
    common/message/function/imagemessage.cpp \
    common/message/function/filemessage.cpp \
    common/message/loginout/getlistmessage.cpp

HEADERS  += window/mainwindow.h \
    server/sqlite.h \
    server/helper.h \
    server/md5/md5.h \
    common/message/base/message.h \
    common/user.h \
    common/message/loginout/loginmessage.h \
    common/message/loginout/loginfeedbackmessage.h \
    common/message/loginout/logoutmessage.h \
    common/message/friendlist/getfriendlistmessage.h \
    common/message/friendlist/friendlistmessage.h \
    common/message/loginout/onlinemessage.h \
    common/message/loginout/offlinemessage.h \
    common/message/addfriend/addfriendmessage.h \
    common/message/addfriend/newfriendmessage.h \
    common/message/addfriend/requestfriendmessage.h \
    common/message/addfriend/ajfriendmessage.h \
    common/message/searchuser/searchusermessage.h \
    common/message/searchuser/userinfomessage.h \
    common/message/function/p2pmessage.h \
    common/message/function/forcelogoutmessage.h \
    common/message/function/forcereloginmessage.h \
    common/message/function/connecttestmessage.h \
    common/message/function/connectokmessage.h \
    server/myclient.h \
    common/allmessage.h \
    common/message/reg/regusermessage.h \
    common/message/reg/regfeedbackmessage.h \
    common/message/base/requestmessage.h \
    common/message/base/usernamemessage.h \
    common/message/base/upmessage.h \
    common/message/base/feedbackmessage.h \
    common/message/base/uumessage.h \
    common/message/loginout/listmessage.h \
    common/message/function/imagemessage.h \
    common/message/function/filemessage.h \
    common/message/loginout/getlistmessage.h

FORMS    += window/mainwindow.ui
#LIBS += "F:/QtCreate/testServerGUI/MySqlDLL.lib"
