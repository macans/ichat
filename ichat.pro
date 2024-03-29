#-------------------------------------------------
#
# Project created by QtCreator 2015-07-01T01:57:10
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += sql
QT       += script
QT       += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ichat
TEMPLATE = app


SOURCES += main.cpp\
    logindialog.cpp \
    mainpanel.cpp \
    chatwindow.cpp \
    addwindow.cpp \
    additems.cpp \
    dividewindow.cpp \
    confirmwindow.cpp \
    addfinishedwindow.cpp \
    userinfo.cpp \
    groupinfo.cpp \
    friendinfo.cpp \
    useritem.cpp \
    renamedialog.cpp \
    deleteconfirmdialog.cpp \
    newgroupdialog.cpp \
    changegroupdialog.cpp \
    Level.cpp \
    chatmsgdlg.cpp

HEADERS  += \
    logindialog.h \
    mainpanel.h \
    chatwindow.h \
    addwindow.h \
    additems.h \
    dividewindow.h \
    confirmwindow.h \
    addfinishedwindow.h \
    userinfo.h \
    groupinfo.h \
    friendinfo.h \
    useritem.h \
    renamedialog.h \
    deleteconfirmdialog.h \
    newgroupdialog.h \
    msgnode.h \
    changegroupdialog.h \
    Level.h \
    connect.h \
    chatmsgdlg.h

FORMS    += \
    logindialog.ui \
    mainpanel.ui \
    chatwindow.ui \
    addwindow.ui \
    additems.ui \
    dividewindow.ui \
    confirmwindow.ui \
    addfinishedwindow.ui \
    userinfo.ui \
    groupinfo.ui \
    friendinfo.ui \
    useritem.ui \
    renamedialog.ui \
    deleteconfirmdialog.ui \
    newgroupdialog.ui \
    changegroupdialog.ui \
    chatmsgdlg.ui

RESOURCES += \
    resource.qrc

