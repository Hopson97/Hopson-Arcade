#!/bin/bash

if [ "$1" = "release" ]
then
    ./bin/release/hopson-arcade 
else
    ./bin/debug/hopson-arcade 
fi