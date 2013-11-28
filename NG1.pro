#-------------------------------------------------
#
# Project created by QtCreator 2013-11-14T11:35:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += serialport

TARGET = NG1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    settingsdialog.cpp \
    simpleplot.cpp

HEADERS  += mainwindow.h \
    settingsdialog.h \
    simpleplot.h

FORMS    += mainwindow.ui \
    settingsdialog.ui

# Платформа Windows  [Переключить]
# Версия библиотеки Qwt 6.1.0  [Переключить]
INCLUDEPATH += C:/qwt-6.1.0/include
# Конфигурация сборки Отладка (Debug)   [Переключить]
LIBS += -LC:/qwt-6.1.0/lib -lqwtd
