CC = gcc
SRC = src/main.c src/game.c src/board.c src/tile.c src/menu.c
all:
	$(CC) -Wall $(SRC) -Iinclude -Llib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o main.exe
