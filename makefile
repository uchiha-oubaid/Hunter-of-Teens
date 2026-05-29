# Compiler and flags
CC = g++
CFLAGS = `sdl2-config --cflags`
LIBS = `sdl2-config --libs` -lSDL2_image
FLAGS = -g -Wall
TARGET = build/game
SRC = src/main.cpp src/game.cpp src/player.cpp

# Default target
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS) $(FLAGS)

# Clean build files
clean:
	rm -f $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean run
