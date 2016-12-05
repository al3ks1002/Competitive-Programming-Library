#!/bin/bash

# Prints the menu (so that you can grep easier).

index=0
for file in $(find ../src -name "*.cpp" | sort); do
    printf "[%s] $file\n" "$index"
    ((++index))
done

