#!/bin/sh

EXEC="./build/a.out"

make

if [ $? -eq 0 ]
then
    echo Running $EXEC:
    echo 
    $EXEC $@
else
    echo ERROR: Compilation Error
fi
