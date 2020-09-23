QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aspect_ratio_widget.cpp \
    game.cpp \
    interface.cpp \
    main.cpp \
    main_window.cpp \
    mine_counter.cpp \
    mine_field.cpp \
    timer.cpp

HEADERS += \
    aspect_ratio_widget.h \
    game.h \
    interface.h \
    main_window.h \
    mine_counter.h \
    mine_field.h \
    timer.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    resources.qrc
