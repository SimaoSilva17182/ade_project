QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addnewcustomer.cpp \
    addnewgame.cpp \
    addnewseller.cpp \
    customertable.cpp \
    gametable.cpp \
    main.cpp \
    mainwindow.cpp \
    sales.cpp \
    sellertable.cpp

HEADERS += \
    addnewcustomer.h \
    addnewgame.h \
    addnewseller.h \
    customertable.h \
    gametable.h \
    mainwindow.h \
    sales.h \
    sellertable.h

FORMS += \
    addnewcustomer.ui \
    addnewgame.ui \
    addnewseller.ui \
    customertable.ui \
    gametable.ui \
    mainwindow.ui \
    sales.ui \
    sellertable.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Pictures.qrc
