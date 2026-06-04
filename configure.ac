# SPDX-License-Identifier: CC0-1.0
# This file is in the public domain under CC0 1.0 Universal
AC_INIT([twlegacy], [1.0])
AM_INIT_AUTOMAKE([-Wall foreign subdir-objects])

AC_PROG_CXX
AC_PROG_CC

# check for Windows resource compiler (MinGW only useful case)
AC_CHECK_TOOL([WINDRES], [windres])

if test -z "$WINDRES"; then
    AC_MSG_WARN([windres not found - Windows resources will not be built])
fi

# flags for different systems
AC_CANONICAL_HOST

case "$host_os" in
    mingw*|cygwin*)
        WIN32=true
        AC_DEFINE([PLATFORM_WINDOWS], [1], [Windows build])
        ;;
    *)
        WIN32=false
        AC_DEFINE([PLATFORM_LINUX], [1], [Linux build])
        ;;
esac

AC_CHECK_HEADERS([SDL/SDL.h SDL/SDL_image.h SDL/SDL_mixer.h], [],
    [AC_MSG_ERROR([SDL headers not found])])

# finding libraries
AC_CHECK_LIB([SDL], [SDL_Init], [], [AC_MSG_ERROR([SDL not found])])
AC_CHECK_LIB([SDL_image], [IMG_Load], [], [AC_MSG_ERROR([SDL_image not found])])
AC_CHECK_LIB([SDL_mixer], [Mix_OpenAudio], [], [AC_MSG_ERROR([SDL_mixer not found])])

# output
AC_CONFIG_FILES([Makefile])
AC_OUTPUT