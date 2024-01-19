QT       += core gui
QT           += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    another_window.cpp \
    create_question.cpp \
    editing_test.cpp \
    main.cpp \
    mainwindow.cpp \
    student_testing.cpp \
    student_window.cpp \
    teacher_window.cpp \
    viewing_results.cpp

HEADERS += \
    another_window.h \
    create_question.h \
    editing_test.h \
    mainwindow.h \
    student_testing.h \
    student_window.h \
    teacher_window.h \
    viewing_results.h

FORMS += \
    another_window.ui \
    create_question.ui \
    editing_test.ui \
    mainwindow.ui \
    student_testing.ui \
    student_window.ui \
    teacher_window.ui \
    viewing_results.ui

TRANSLATIONS += \
    creating_tests_ru_RU.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
