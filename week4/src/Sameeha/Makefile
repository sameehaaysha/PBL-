CC = gcc
CFLAGS = -Wall -Wextra -g
GTK_FLAGS = $(shell pkg-config --cflags --libs gtk+-3.0)

TARGET = page_replacement

SOURCES = main.c gui.c ../Joannes/fifo.c ../Riya/lru.c ../shashwath/optimal.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -DPAGE_REPLACEMENT_GUI $(SOURCES) -o $(TARGET) $(GTK_FLAGS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run