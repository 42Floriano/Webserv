#! /bin/bash

HEAD_FILE=$1
TARGET_FILE=$2
HEAD_LEN=$(wc -l < $1)

echo checking if $TARGET_FILE has $HEAD_FILE head;

if diff $HEAD_FILE <(head -n$HEAD_LEN $TARGET_FILE) > /dev/null ; then
	echo file $2 : nothing to do;
else
	echo file $2 : writing head;
	cp $TARGET_FILE ${TARGET_FILE}.orig;
	{
		cat $HEAD_FILE; cat ${TARGET_FILE}.orig
	} > $TARGET_FILE;
fi
