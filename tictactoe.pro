QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++23

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

unix {
    QMAKE_CXXFLAGS_RELEASE += -s -Wall -Werror -O2
    QMAKE_CXXFLAGS_DEBUG +=  -Wall -Wextra -Werror -g
}

win32{
    QMAKE_CXXFLAGS_RELEASE += -s -Wall -Werror -O3
    QMAKE_CXXFLAGS_DEBUG +=  -Wall -Wextra -Werror -g
}


DEFINES += TTT_DEBUG

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/newgamedialog.cpp \
    src/tbutton.cpp \
    src/tictactoe.cpp

HEADERS += \
    src/mainwindow.h \
    src/newgamedialog.h \
    src/tbutton.h \
    src/tictactoe.h

FORMS += \
    src/main.ui

TRANSLATIONS += \
    src/tictactoe_pt_BR.ts
CONFIG += lrelease
CONFIG += embed_translations

RESOURCES += \
    src/resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
