#-------------------------------------------------
#
# Project created by QtCreator 2014-03-31T23:05:21
# 串口支持，打印支持，添加qcustomplot库
#-------------------------------------------------

QT       += core gui
QT       += serialport
QT       += widgets printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SerialPort
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    qcustomplot.cpp

HEADERS  += widget.h \
    qcustomplot.h

FORMS    += widget.ui
