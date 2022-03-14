#-------------------------------------------------
#
# Project created by QtCreator 2018-10-16T19:13:44
#
#-------------------------------------------------

QT       += core gui
QT      +=network
CONFIG+=resources_big

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Elf_Must_Die_3
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    Attack.cpp \
    PetElf.cpp \
    FightingElf/Petelffighting.cpp \
    global.cpp \
    Battle.cpp \
    User.cpp \
    tcp_deal.cpp \
    Frash.cpp \
    speed.cpp \
    Init_other.cpp \
    Elf_show.cpp \
    Fighting_show.cpp \
    Choose_mode.cpp \
    FightingElf/Life.cpp \
    FightingElf/Defence.cpp \
    FightingElf/Agility.cpp \
    FightingElf/Power.cpp \
    FightingElf/Skill.cpp \
    suggestion.cpp

HEADERS  += mainwindow.h \
    Attack.h \
    PetElf.h \
    FightingElf/Petelffighting.h \
    global.h \
    Battle.h \
    User.h \
    FightingElf/AdvanceElf.h \
    suggestion.h

FORMS    += mainwindow.ui \
    suggestion.ui

RESOURCES += \
    touxiang.qrc
