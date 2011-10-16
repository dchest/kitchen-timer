CC=gcc
CFLAGS=-c -Wall -O2
CFLAGS+=`pkg-config --cflags gtk+-2.0`
GTK_LIBS=`pkg-config --libs gtk+-2.0`


SRC=kitchen-timer.c
OBJ=$(SRC:.c=.o)
EXE=kitchen-timer

all: $(SRC) $(EXE)

$(EXE): $(OBJ)
	$(CC) $(LDFLAGS) $(GTK_LIBS) $(OBJ) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJ) $(EXE)

