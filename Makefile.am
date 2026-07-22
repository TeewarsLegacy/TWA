bin_PROGRAMS = twlegacy

AM_CXXFLAGS = $(SDL_CFLAGS)

twlegacy_SOURCES = \
    src/main.cpp \
    src/client.cpp \
    src/server.cpp \
    src/network.cpp \
    src/screen.cpp \
    src/game.cpp \
    src/menu.cpp \
    src/map.cpp \
    src/audio.cpp \
    logo.rc

# Спочатку плагіни, а в самому кінці розгортається $(SDL_LIBS) з мережею
twlegacy_LDADD = -lSDL_image -lSDL_mixer -lSDL_gfx $(SDL_LIBS)
