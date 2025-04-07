QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QMAKE_CXXFLAGS_RELEASE += -s -Wall -Werror -O3
QMAKE_CXXFLAGS_DEBUG +=  -Wall -Wextra -Werror  -g


SOURCES += \
    main.cpp \
    mainwindow.cpp \
    newgamedialog.cpp \
    tbutton.cpp \
    tictactoe.cpp

HEADERS += \
    mainwindow.h \
    newgamedialog.h \
    tbutton.h \
    tictactoe.h

FORMS += \
    main.ui

TRANSLATIONS += \
    tictactoe_pt_BR.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
