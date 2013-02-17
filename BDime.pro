#-------------------------------------------------
#
# Project created by QtCreator 2013-02-11T21:42:20
#
#-------------------------------------------------

QT       += core gui sql

TARGET = BDime
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dbdriver.cpp \
    parser.cpp \
    dialogs.cpp \
    temptablemodel.cpp \
    tablerow.cpp \
    vendordelegate.cpp

HEADERS  += mainwindow.h \
    dbdriver.h \
    parser.h \
    dialogs.h \
    temptablemodel.h \
    tablerow.h \
    vendordelegate.h

FORMS    += mainwindow.ui
