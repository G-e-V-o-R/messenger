QT += core gui network websockets widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# Include directories
INCLUDEPATH += /usr/local/include
INCLUDEPATH += /home/gevor/Desktop/messenger/proto
INCLUDEPATH += /home/gevor/grpc/include/grpcpp
INCLUDEPATH += /usr/include
INCLUDEPATH +=/usr/lib/x86_64-linux-gnu
# Libraries to link against
LIBS += -L/usr/lib/x86_64-linux-gnu \
        -lgrpc++ -lgrpc -lgrpc++_unsecure \
        -lgrpc++_alts -lgrpcpp_channelz -lgrpc++_reflection \
        -lgrpc++_error_details

# Source files
SOURCES += \
    chatwidget.cpp \
    customlineEdit.cpp \
    logwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    regwidjet.cpp

# Header files
HEADERS += \
    InputType.h \
    chatwidget.h \
    customlineEdit.h \
    logwidget.h \
    mainwindow.h \
    regwidget.h \
    separator.h \
    websocketclient.h

# Forms
FORMS += \
    mainwindow.ui

# Additional files
DISTFILES += \
    ../../Downloads/lock.png \
    ../../Downloads/mail.png \
    ../../Downloads/person.png
