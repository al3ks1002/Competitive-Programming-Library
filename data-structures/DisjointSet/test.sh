#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: ./test.sh my_source_code.cpp"
    exit 1
fi

source=$1
if [ ! -e $source ]; then
    echo "File does not exist"
    exit 1
fi

g++ -w -std=c++14 -O2 -o mlc $source
if [ $? != 0 ]; then
    echo "Compilation error"
    exit 1
fi

for testfile in `find tests/ -name "test*.in" | sort --version-sort`; do
    touch out
    runtime=`(TIMEFORMAT='%3R'; time ./mlc < $testfile > out) 2>&1`

    ok=`echo $testfile | cut -d \. -f 1 | cut -d \/ -f 2`
    ok="tests/${ok}.ok"

    testnumber=`echo $testfile | sed 's/[^0-9]//g'`
    message="Test ${testnumber} | ${runtime}"

    dwdiff out $ok > /dev/null
    if [ $? != 0 ]; then
        message="${message} | Wrong Answer"
    else
        message="${message} | Correct"
    fi

    echo $message
    rm out
done

rm mlc
