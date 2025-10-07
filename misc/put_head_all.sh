#! /bin/bash

srcdir=./$1

TARGETS=$(find $srcdir -name '*.cpp' -o -name '*.hpp' -o -name '*.tpp')

for file in $TARGETS; do
	echo $file
	./put_head.sh ./LICENSE.h $file;
done
