QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
aspect_ratio_widget.cpp \
	clickable_label.cpp \
	custom_game_size.cpp \
	game.cpp \
	icon.cpp \
	interface.cpp \
	main.cpp \
	main_window.cpp \
	mine_counter.cpp \
	mine_field.cpp \
	new_game_selection.cpp \
	size_selection.cpp \
	timer.cpp

HEADERS += \
aspect_ratio_widget.h \
	clickable_label.h \
	custom_game_size.h \
	game.h \
	icon.h \
	interface.h \
	main_window.h \
	mine_counter.h \
	mine_field.h \
	new_game_selection.h \
	size_selection.h \
	timer.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
resources.qrc

RC_ICONS = resources/mine.ico
