INSTALL_DIR=/usr/local
RM=/bin/rm -vf
CC=gcc
CXX=g++
ECHO=/bin/echo -e
LD=ld

PWD=pwd
CDR=$(shell pwd)


LDFLAGS=-shared
override CXXFLAGS+= -O2 -fPIC -Wall -I include/

EDLDFLAGS:=$(LDFLAGS)

LIBEXT=so
LINKOPTIONS:=-shared
RMDIR=rmdir -v

TARGETLIB=libmcp9808.$(LIBEXT)
LINKOPTIONS:=-L build/

lib_objects = src/libmcp9808.o
lib_example = example/test.cpp

all: build/$(TARGETLIB) build/test

build:
	mkdir build

build/$(TARGETLIB): $(lib_objects) build
	$(LD) $(LDFLAGS) $(lib_objects) -o $@

build/test: $(lib_example)
	$(CXX) -o $@ -Iinclude/ $(LINKOPTIONS) $(lib_example) -lmcp9808
test: build/test
	sudo LD_LIBRARY_PATH=./build ./build/test

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

install: build/$(TARGETLIB)
	cp $< $(INSTALL_DIR)/lib/$(TARGETLIB)
	cp include/* $(INSTALL_DIR)/include/


clean:
	$(RM) $(lib_objects) 
	$(RM) build/test

spotless: clean
	$(RM) build/$(TARGETLIB)
	$(RMDIR) build

uninstall:
	$(RM) $(INSTALL_DIR)/lib/$(TARGETLIB)
	$(RM) $(INSTALL_DIR)/include/libmcp9808.h