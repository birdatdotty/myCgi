TEMPLATE = lib
TARGET = MyCgi2RouteTest
QT += qml quick
CONFIG += plugin c++11

TARGET = $$qtLibraryTarget($$TARGET)
uri = MyCgi2RouteTest

# Input
SOURCES += \
        mycgi2routetest_plugin.cpp \
        mycgi2routetest.cpp

HEADERS += \
        mycgi2routetest_plugin.h \
        mycgi2routetest.h

DISTFILES = qmldir

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) "$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)" "$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir
unix {
    installPath = /usr/local/lib/myCgi2/plugins/$$replace(uri, \., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}

INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/include
LIBS += -L/usr/local/lib/ -lObj -lRouter
