#!/bin/sh

. ../../../../cross_defs.dj

exec make -f Makefile.dj CC=$TARGET-gcc AR=$TARGET-ar $*
