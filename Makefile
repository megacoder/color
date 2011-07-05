CC = gcc
CFLAGS = -W -Wall -O2 -g 
INCLUDE = $(wildcard *.h)
OBJS = color.o
EXE = color

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

install: all
	cp $(EXE) /usr/local/bin

clean:
	rm -f $(EXE) $(OBJS)

