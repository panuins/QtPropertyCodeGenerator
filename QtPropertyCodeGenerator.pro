#-------------------------------------------------
#
# Project created by QtCreator 2014-04-29T17:26:29
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtPropertyCodeGenerator
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    property.cpp \
    propertydata.cpp \
    dialogset.cpp \
    dialogedit.cpp \
    classsettings.cpp \
    propertiesgroup.cpp \
    propertiesgroupdata.cpp \
    enumtype.cpp

HEADERS  += widget.h \
    property.h \
    propertydata.h \
    sharedFunctions.h \
    dialogset.h \
    dialogedit.h \
    propertyInlineFunctions.h \
    classsettings.h \
    propertiesgroup.h \
    propertiesgroupdata.h \
    propertiesgroupInlineFunctions.h \
    enumtype.h

FORMS    += widget.ui \
    dialogset.ui \
    dialogedit.ui

CONFIG(debug, debug|release) {
    DEFINES += DEBUG
    win32 {
    }
    unix {
    }
}
else {
    win32 {
    }
    unix {
    }
}
