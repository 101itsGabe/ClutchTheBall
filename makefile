#Compiler Flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Isrc -Isrc/include -Isrc/include/SDL2

#Linker Flags & Platform Exclusivities

ifeq ($(OS), Windows_NT)
#Windows Config
	LDFLAGS = -Lsrc/lib -lSDL2 -lSDL2_ttf -lSDL2_image
	EXECUTABLE :=$(EXECUTABLE).exe
	DEL_CMD := del
else
#MacOs Config
	LDFLAGS = $(shell pkg-config --libs sdl2 SDL2_ttf SDL2_image)
	DEL_CMD := rm
endif


#Source Files
SRC_FILES = main.cpp src/menu.cpp src/gameManager.cpp src/tile.cpp src/player.cpp src/tileManager.cpp src/playerManager.cpp src/aiPlayer.cpp  src/SDLManager.cpp
EXECUTABLE = main

#Platform Exclusivities


all: $(EXECUTABLE)

$(EXECUTABLE): $(SRC_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	$(DEL_CMD) $(EXECUTABLE)