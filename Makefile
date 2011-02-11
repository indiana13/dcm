SRC 	:= src

CC	:= gcc
CFLAGS	:= -c -O2
.ifdef DEBUG
CFLAGS	+= -g
.endif

.SUFFIXES:
.SUFFIXES: .o .c

all: build_dist build_test run_tests

.c.o:
	$(CC) $(CFLAGS) $<

include $(SRC)/Makefile.in
