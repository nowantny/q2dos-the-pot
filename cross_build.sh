#!/bin/sh

. ./cross_defs.dj

if test "$1" = "strip"; then
	echo $TARGET-strip q2.exe
	$TARGET-strip q2.exe
	exit 0
fi

exec make CC=$TARGET-gcc -f Makefile.dj $*
