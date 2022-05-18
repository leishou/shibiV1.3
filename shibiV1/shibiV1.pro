QT       += core gui
QT +=axcontainer
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT  += quickwidgets
QT +=core sql
QT       += multimedia
QT       += multimediawidgets
QT       += core gui network
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    fanqie.cpp \
    frmlunarcalendarwidget.cpp \
    listdo.cpp \
    login.cpp \
    lunarcalendarinfo.cpp \
    lunarcalendaritem.cpp \
    lunarcalendarwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    noticewidegt.cpp \
    share.cpp \
    shibi.cpp \
    stopwatchpagewidget.cpp \
    timerpagewidget.cpp \
    todolist.cpp \
    todomodel.cpp \
    widget.cpp

HEADERS += \
    fanqie.h \
    frmlunarcalendarwidget.h \
    listdo.h \
    login.h \
    lunarcalendarinfo.h \
    lunarcalendaritem.h \
    lunarcalendarwidget.h \
    mainwindow.h \
    noticewidget.h \
    share.h \
    shibi.h \
    stopwatchpagewidget.h \
    timerpagewidget.h \
    todolist.h \
    todomodel.h \
    ui_listdo.h \
    ui_mainwindow.h \
    ui_stopwatchpagewidget.h \
    ui_timerpagewidget.h \
    widget.h

FORMS += \
    fanqie.ui \
    frmlunarcalendarwidget.ui \
    listdo.ui \
    login.ui \
    mainwindow.ui \
    shibi.ui \
    stopwatchpagewidget.ui \
    timerpagewidget.ui \
    widget.ui
LIBS += -ldwmapi
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc \
    main_lun.qrc

DISTFILES += \
    ToDoList.qml \
    main.qml
