#-------------------------------------------------
#
# Project created by QtCreator 2019-08-08T11:06:58
#
#-------------------------------------------------

QT       += core gui printsupport #serialport
QT       += bluetooth androidextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CardioCheck
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    bebe_data_class.cpp \
    plot.cpp \
    plotpoint.cpp \
    qcustomplot.cpp \
    qlabel_button.cpp

HEADERS += \
        mainwindow.h \
    bebe_data_class.h \
    plot.h \
    plotpoint.h \
    qcustomplot.h \
    qlabel_button.h

FORMS += \
        mainwindow.ui

CONFIG += mobility
MOBILITY = 

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android-sources

DISTFILES += \
    android-sources/AndroidManifest.xml

RESOURCES += \
    assets.qrc
