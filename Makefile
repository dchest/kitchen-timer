CC=gcc
CFLAGS=-g -Wall
PKG_CONFIG=-export-dynamic `pkg-config --libs --cflags gtk+-2.0`

SRCS=kitchen-timer.c
OBJS=$(SRCS:.c=.o)
EXE=kitchen-timer

all: $(SRCS) $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(EXE) $(PKG_CONFIG)

clean:
	rm $(OBJS) $(EXE)

