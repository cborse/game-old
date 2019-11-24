CC = gcc
CFLAGS = -std=c11 -Iinclude -Wno-deprecated-declarations
LIBS = -lcsfml-system -lcsfml-graphics -lcsfml-audio -lcsfml-window
SRC = $(shell find src -name *.c)

all:
	$(CC) -o game $(CFLAGS) $(LIBS) $(SRC)
