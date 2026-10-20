CC = gcc
CFLAGS = -Wall -Wextra -std=c11

GTK_CFLAGS = $(shell pkg-config --cflags gtk+-3.0)
GTK_LIBS = $(shell pkg-config --libs gtk+-3.0)

TARGET = deadlock_simulator

SRC = main.c \
      ../joannes/process.c \
      ../shashwath/deadlock.c \
      ../riya/gui.c

INCLUDES = -I. \
           -I../joannes \
           -I../shashwath \
           -I../riya

all:
	$(CC) $(CFLAGS) $(GTK_CFLAGS) $(INCLUDES) $(SRC) -o $(TARGET) $(GTK_LIBS)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)
