#!/bin/bash

if [ $# -ne 2 ]; then
    echo "usage: ./transform_tests.sh begin end"
    exit 1
fi

for ((i=$1; i<=$2; i++)); do
    mv grader_test$i.in test$i.in;
    mv grader_test$i.ok test$i.ok;
done
