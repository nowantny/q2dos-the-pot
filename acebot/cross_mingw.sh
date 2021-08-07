#!/bin/sh

. ../cross_defs.mingw

if test "$1" = "strip"; then
	echo $TARGET-strip gamex86.dll
	$TARGET-strip gamex86.dll
	exit 0
fi

exec make CC=$TARGET-gcc -f Makefile.mingw $*
