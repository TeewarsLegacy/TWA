# Copyright (c) 2026 mykyta polishyk, see license.txt for more info #

# Cpp compiler
CXX = g++
# Targets
TARGETS = src/main.cpp \
	  src/client.cpp \
	  src/server.cpp \
	  src/network.cpp \
	  src/screen.cpp \
	  src/game.cpp \
	  src/menu.cpp \
	  src/map.cpp \
	  src/audio.cpp
# Output
EXEC = teewarslegacy
# Linker flags
LDFLAGS = -lSDL -lSDL_image -lSDL_gfx -lSDL_mixer

all:
	$(CXX) $(TARGETS) $(LDFLAGS) -o $(EXEC)
