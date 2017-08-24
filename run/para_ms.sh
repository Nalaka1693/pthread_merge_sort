#!/usr/bin/env bash
cd ../
gcc -o pms parallel_merge_sort.c -lpthread
unamestr=`uname`
if [[ "$unamestr" == 'Linux' ]]; then
   ./pms
    sleep 5
    rm -rf pms
elif [[ "$unamestr" == 'MINGW64_NT-10.0' ]]; then
    ./pms.exe
    sleep 5
    rm -rf pms.exe
fi