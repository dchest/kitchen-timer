CC=gcc
CFLAGS=-Wall -O2
CFLAGS+=`pkg-config --cflags gtk+-2.0 glib-2.0`
GTKLIBS=`pkg-config --libs gtk+-2.0 glib-2.0`


SRC=kitchen-timer.c
EXE=kitchen-timer
OBJS = kitchen-timer.o

$(EXE): $(OBJS)
	$(CC) $(LDFLAGS) -o $(EXE) $(OBJS) $(GTKLIBS)

kitchen-timer.o: kitchen-timer.c
	$(CC) $(CFLAGS) -c kitchen-timer.c

clean:
	rm $(OBJS) $(EXE)

install:
	cp kitchen-timer.desktop /usr/share/applications/
	mv kitchen-timer /usr/local/bin/
