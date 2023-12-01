QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    add_word.cpp \
    forget_password.cpp \
    main.cpp \
    challenger.cpp\
    gaming.cpp\
    matching.cpp \
    pvp.cpp \
    questioner.cpp\
    sign_in.cpp\
    sign_up.cpp\
    tcp_connection.cpp \
    user.cpp\
    user_mainwindow.cpp\
    user_database.cpp\
    word_database.cpp

HEADERS += \
    add_word.h \
    challenger.h\
    forget_password.h \
    gaming.h\
    matching.h \
    pvp.h \
    questioner.h\
    sign_in.h\
    sign_up.h\
    tcp_connection.h \
    user.h\
    user_mainwindow.h\
    user_database.h\
    word_database.h

FORMS += \
    add_word.ui \
    forget_password.ui \
    gaming.ui\
    matching.ui \
    pvp.ui \
    sign_in.ui\
    sign_up.ui\
    user_mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc
