#!/bin/sh

EXEC_FOLDER="./build/examples"

EXE=
if [ -z $1 ]
then
    EXE=$EXEC_FOLDER/default
    echo No example provided
else
    EXE=$EXEC_FOLDER/$1
    shift
fi

make $EXE 

if [ $? -eq 0 ]
then
    echo Running $EXE:
    echo 
    $EXE $@
else
    echo ERROR: Compilation Error
fi
