#!/bin/bash

if [ "$1" = "release" ]
then
    ./bin/release/<PNAME> 
else
    ./bin/debug/<PNAME> 
fi