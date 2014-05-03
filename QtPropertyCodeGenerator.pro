#-------------------------------------------------
#
# Project created by QtCreator 2014-04-29T17:26:29
#
#-------------------------------------------------
# QtPropertyCodeGenerator.pro: Qt Project File
# ------------------------------------------------------------------------------
# Authors: panuins <panuins@gmail.com>
#
# This program is free software; you can redistribute it and/or modify it
# under the terms of the GPLv2 or later as published by the Free Software
# Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
# ------------------------------------------------------------------------------

QT       += core gui

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
