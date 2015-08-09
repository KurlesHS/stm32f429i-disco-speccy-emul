TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    z80.c \
    codegen/opcodes_impl.c

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    z80.h \
    codegen/opcodes_decl.h \
    codegen/opcodes_table.h

