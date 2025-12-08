BUILD = pacman
CC = g++
SRC_FILES = ./src/entity.cpp ./src/ghost.cpp ./src/tile_grid.cpp ./src/Trigger.cpp ./src/pacman.cpp ./src/ray.cpp
OBJECTS = ./src/entity.o ./src/ghost.o ./src/tile_grid.o ./src/Trigger.o ./src/pacman.o ./src/ray.o
RAYLIB = "C:\raylib-5.5\src"
HEADERS = ./headers
CFLAGS = -ggdb -I $(HEADERS) -I $(RAYLIB) -Wall -Wextra -O2 -fpermissive
LDFLAGS = -LC:\raylib-5.5\src -lraylib -lopengl32 -lgdi32 -lwinmm

all : $(BUILD)

$(BUILD) : $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS) 

%.o : %.cpp
	$(CC) $(CFLAGS) -c -o $@ $^
.PHONY : clean
clean :
	-rm $(OBJECTS)
