TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        head.cpp \
    network.cpp \
    Neurons/neuron.cpp \
    tokenizer.cpp \

HEADERS += \
    Neurons/neuron.hpp \
    network.hpp \
    tokenizer.hpp \
