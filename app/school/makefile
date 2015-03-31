.PHONY: all debug release build clean temp depend

_ABS_PATH = $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
_REL_PATH = ../..
include ../../reflex.mk

_SRCS = $(wildcard *.c) $(wildcard *.cc) $(wildcard *.cpp)
_OBJS = $(addsuffix .o,$(basename $(_SRCS)))
_EXEC = $(shell basename $(PWD))

CPPFLAGS += -std=c++11 -Wall -g -I/usr/include/libxml2

LDLIBS += -lxml2 -lglog

all: release

debug: CPPFLAGS += -O0
debug: build

release: CPPFLAGS += -O2
release: build

build: $(_EXEC)

$(_OBJS): $(MAKEFILE_LIST)

$(_EXEC): $(_OBJS) $(MAKEFILE_LIST)
	$(LINK.cc) -o $@ $(_OBJS) $(LOADLIBES) $(LDLIBS)
	
clean:
	rm -rf *_rflx.cpp
	rm -rf ./.depend
	rm -rf $(_OBJS)
	rm -rf $(_EXEC)

temp:
	@echo "MAKEFILE_LIST="$(MAKEFILE_LIST)

depend: .depend

.depend: person.h school.h teacher.h student.h $(MAKEFILE_LIST)
	../../bin/genreflex person.h
	../../bin/genreflex school.h
	../../bin/genreflex teacher.h
	../../bin/genreflex student.h
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $(_SRCS) > ./.depend

include .depend
