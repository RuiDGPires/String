#!/bin/sh

TEST_FOLDER="./build/tests"

make tests

if [ $? -eq 0 ]
then
    for EXE in "$TEST_FOLDER"/*
    do
        $EXE
    done
else
    echo ERROR: Compilation Error
fi
