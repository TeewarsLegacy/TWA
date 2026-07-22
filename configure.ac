# SPDX-License-Identifier: CC0-1.0
# This file is in the public domain under CC0 1.0 Universal
AC_INIT([twlegacy], [1.0])
AM_INIT_AUTOMAKE([-Wall foreign subdir-objects])

AC_PROG_CXX
AC_PROG_CC

SDL_CFLAGS=`sdl-config --cflags`
SDL_LIBS=`sdl-config --libs`

AC_CHECK_TOOL([WINDRES], [windres])

if test -z "$WINDRES"; then
    AC_MSG_WARN([windres not found - Windows resources will not be built])
fi

AC_CANONICAL_HOST

case "$host_os" in
    mingw*|cygwin*)
        WIN32=true
        AC_DEFINE([PLATFORM_WINDOWS],, [Windows build])
        # Додаємо мережу Winsock
        SDL_LIBS="$SDL_LIBS -lws2_32"
        # Фікс шляхів для SDL_gfx
        SDL_CFLAGS="$SDL_CFLAGS -I`sdl-config --prefix`/include/SDL"
        ;;
    *)
        WIN32=false
        AC_DEFINE([PLATFORM_LINUX],, [Linux build])
        ;;
esac

AC_CHECK_HEADERS([SDL/SDL.h SDL/SDL_image.h SDL/SDL_mixer.h], [],
    [AC_MSG_ERROR([SDL headers not found])])

AC_CHECK_LIB([SDL], [SDL_Init], [:], [AC_MSG_ERROR([SDL not found])])
AC_CHECK_LIB([SDL_image], [IMG_Load], [:], [AC_MSG_ERROR([SDL_image not found])])
AC_CHECK_LIB([SDL_mixer], [Mix_OpenAudio], [:], [AC_MSG_ERROR([SDL_mixer not found])])

AC_SUBST([SDL_CFLAGS])
AC_SUBST([SDL_LIBS])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
