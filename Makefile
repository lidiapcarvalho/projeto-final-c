CC = gcc

CFLAGS = -I/ucrt64/include/ncurses

LDFLAGS = -lncursersw

TARGET = corrida

SOURCES = main.c game.c track.c

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) $(LDFLAGS) -o $(TARGET)
	