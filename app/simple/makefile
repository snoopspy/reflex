.PHONY: all debug release build clean temp depend

include ../../reflex.mk

_SRCS = $(wildcard *.c) $(wildcard *.cc) $(wildcard *.cpp)
_OBJS = $(addsuffix .o,$(basename $(_SRCS)))
_EXEC = $(shell basename $(PWD))

CPPFLAGS += -Wall -g

LDLIBS += -lpthread

all: release

debug: CPPFLAGS += -O0
debug: build

release: CPPFLAGS += -O2
release: build

build: $(_EXEC)

$(_OBJS): $(MAKEFILE_LIST)

$(_EXEC): $(_OBJS) $(MAKEFILE_LIST)
	$(LINK.cc) -o $@ $(_OBJS) $(LOADLIBES) $(LDLIBS)
	
clean: myobj.h
	rm -rf *_rflx.cpp
	rm -rf ./.depend
	rm -rf $(_OBJS)
	rm -rf $(_EXEC)

temp:
	@echo "MAKEFILE_LIST="$(MAKEFILE_LIST)

depend: .depend

.depend: $(MAKEFILE_LIST)
	../../bin/genreflex myobj.h
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $(_SRCS) > ./.depend

include .depend
