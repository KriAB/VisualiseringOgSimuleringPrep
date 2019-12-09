TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        gsl_math.cpp \
        main.cpp \
        newtonsmovementlaw.cpp \
        vector2d.cpp \
        vector3d.cpp

HEADERS += \
    gsl_math.h \
    math_constants.h \
    newtonsmovementlaw.h \
    vector2d.h \
    vector3d.h
