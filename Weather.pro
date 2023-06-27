QT       += core gui
QT += gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20
CONFIG += rtti

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    WeatherAPI.cpp \
    dailyforecastline.cpp \
    dailyforecastwidget.cpp \
    datewidget.cpp \
    feelslikewidget.cpp \
    format.cpp \
    hourlyforecastline.cpp \
    hourlyforecastwidget.cpp \
    informationwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    smoothscrollarea.cpp \
    sunwidget.cpp \
    weatherAPI.h \
    windwidget.cpp

HEADERS += \
    dailyforecastline.h \
    dailyforecastwidget.h \
    datewidget.h \
    feelslikewidget.h \
    format.hpp \
    hourlyforecastline.h \
    hourlyforecastwidget.h \
    informationwidget.h \
    mainwindow.h \
    smoothscrollarea.h \
    sunwidget.h \
    weatherwidget.h \
    windwidget.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/curl-7.88.1_2-win64-mingw/lib/ -lcurl
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/curl-7.88.1_2-win64-mingw/lib/ -lcurl
else:unix: LIBS += -L$$PWD/lib/curl-7.88.1_2-win64-mingw/lib/ -lcurl

INCLUDEPATH += $$PWD/lib/curl-7.88.1_2-win64-mingw/include
DEPENDPATH += $$PWD/lib/curl-7.88.1_2-win64-mingw/include

INCLUDEPATH += C:\Users\nekof\Desktop\Qt\jsontest\JSONtest\lib\json-develop\include

DISTFILES += \
    config/config.txt \
    libcurl-x64.dll

RESOURCES += \
    assets.qrc

