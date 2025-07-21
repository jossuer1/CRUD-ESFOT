QT += widgets

CONFIG += c++17
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
   

HEADERS += \
    mainwindow.h \
    ../vehiculos.h

FORMS += \
    mainwindow.ui
