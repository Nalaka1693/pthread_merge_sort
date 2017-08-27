#!/usr/bin/env bash
cd ../
gcc -o sms serial_merge_sort.c
unamestr=`uname`
if [[ "$unamestr" == 'Linux' ]]; then
   ./sms
    sleep 2
    rm -rf sms
elif [[ "$unamestr" == 'MINGW64_NT-10.0' ]]; then
    ./sms.exe
    sleep 2
    rm -rf sms.exe
fi
