QT = core
QT += quick
QT += xml
QT += core
QT += widgets
CONFIG += c++17 cmdline


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    main.qml \
    Views/Example.qml

HEADERS += \
    Header/define.h \
    Header/modrmbyte.h \
    Header/resolvent.h \
    Header/readpefile.h \
    Header/bringinstructions.h

SOURCES += \
    Source/bringinstructions.cpp \
    Source/readpefile.cpp \
    Source/modrmbyte.cpp \
    Source/resolvent.cpp \
    main.cpp



RESOURCES += \
    qreSource.qrc
