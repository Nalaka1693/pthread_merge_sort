#!/usr/bin/env bash
cd ../
gcc -o test test.c -lpthread
unamestr=`uname`
if [[ "$unamestr" == 'Linux' ]]; then
   ./test
    sleep 5
    rm -rf test
elif [[ "$unamestr" == 'MINGW64_NT-10.0' ]]; then
    ./test.exe
    sleep 5
    rm -rf test.exe
fi