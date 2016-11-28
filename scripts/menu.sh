#!/bin/bash

# Prints the menu (so that you can grep easier).

index=0
for file in $(find ../src -name "*.cpp" | sort); do
    printf "${ORANGE}[$index] $file\n"
    ((++index))
done

