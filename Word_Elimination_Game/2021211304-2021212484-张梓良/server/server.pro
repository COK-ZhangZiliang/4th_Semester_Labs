QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    challenger.cpp \
    #gaming.cpp \
    main.cpp \
    #mainwindow.cpp \
    questioner.cpp \
    #sign_in.cpp \
    #sign_up.cpp \
    tcp_connection.cpp \
    user.cpp \
    user_database.cpp \
    #user_mainwindow.cpp \
    #widget.cpp \
    word_database.cpp

HEADERS += \
    challenger.h \
    #gaming.h \
    #mainwindow.h \
    questioner.h \
    #sign_in.h \
    #sign_up.h \
    tcp_connection.h \
    user.h \
    user_database.h \
    #user_mainwindow.h \
    #widget.h \
    word_database.h

FORMS += \
    #gaming.ui \
    #mainwindow.ui \
    #sign_in.ui \
    #sign_up.ui \
    #user_mainwindow.ui \
    #widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image/.qrc
