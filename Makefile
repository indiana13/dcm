CC	= gcc
CFLAGS	= -c -O2
.ifdef DEBUG
CFLAGS	+= -g
.endif

