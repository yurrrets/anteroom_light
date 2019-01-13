# Arduino Make file. Refer to https://github.com/sudar/Arduino-Makefile

BOARD_TAG    = nano

LOCAL_CPP_SRCS  ?= $(wildcard src/*.cpp)

include /usr/share/arduino/Arduino.mk

DEVICE_PATH=/dev/ttyUSB*

CPPFLAGS += -std=c++11
