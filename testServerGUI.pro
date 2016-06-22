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
    common/message.cpp \
    common/user.cpp

HEADERS  += mainwindow.h \
    sqlite.h \
    helper.h \
    md5/md5.h \
    common/cJSON.h \
    common/message.h \
    common/user.h

FORMS    += mainwindow.ui
#LIBS += "F:/QtCreate/testServerGUI/MySqlDLL.lib"
