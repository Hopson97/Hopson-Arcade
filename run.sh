#!/bin/bash

if [ "$1" = "release" ]
then
    ./bin/release/astar
else
    ./bin/debug/astar
fi