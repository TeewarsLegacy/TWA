# SPDX-License-Identifier: CC0-1.0
# This file is in the public domain under CC0 1.0 Universal
AC_INIT([mastersrv], [1.0])
AM_INIT_AUTOMAKE([-Wall foreign subdir-objects])

AC_PROG_CXX
AC_PROG_CC

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

# output
AC_CONFIG_FILES([Makefile])
AC_OUTPUT