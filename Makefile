CC = gcc

CFLAGS = -I/ucrt64/include/ncurses

LDFLAGS = -lncursesw

TARGET = corrida

SOURCES = main.c game.c track.c car.c timer.c menu.c
OBJECTS = main.o game.o track.o car.o timer.o menu.o

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(TARGET)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

game.o: game.c game.h
	$(CC) $(CFLAGS) -c game.c

track.o: track.c track.h
	$(CC) $(CFLAGS) -c track.c

car.o: car.c car.h track.h
	$(CC) $(CFLAGS) -c car.c

timer.o: timer.c timer.h
	$(CC) $(CFLAGS) -c timer.c

menu.o: menu.c menu.h
	$(CC) $(CFLAGS) -c menu.c

clean:
	rm -f $(OBJECTS) $(TARGET)
