#-------------------------------------------------
#
# Project created by QtCreator 2019-07-02T08:55:28
#
#-------------------------------------------------

QT       += core gui
QT       += network widgets  multimedia  multimediawidgets
CONFIG += resources_big

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = SmartHome_Test
TEMPLATE = app

SOURCES += main.cpp\
        loginwindow.cpp \
    registerwindow.cpp \
    tcpsocket.cpp \
    serveraddressdialog.cpp \
    userinformation.cpp \
    smartprotocol.cpp \
    functionwindow.cpp \
    devicemanagewindow.cpp \
    forgetpasswordwindow.cpp \
    resetpasswordwindow.cpp \
    camera.cpp \
    game.cpp \
    sendpasswordemail.cpp

HEADERS  += loginwindow.h \
    registerwindow.h \
    tcpsocket.h \
    serveraddressdialog.h \
    userinformation.h \
    smartprotocol.h \
    functionwindow.h \
    devicemanagewindow.h \
    forgetpasswordwindow.h \
    resetpasswordwindow.h \
    camera.h \
    game.h \
    sendpasswordemail.h

FORMS    += loginwindow.ui \
    registerwindow.ui \
    serveraddressdialog.ui \
    functionwindow.ui \
    devicemanagewindow.ui \
    forgetpasswordwindow.ui \
    resetpasswordwindow.ui \
    camera.ui \
    game.ui

RESOURCES += \
    source.qrc

DISTFILES +=
