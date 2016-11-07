#!/bin/bash

# Tests your source code against some tests cases located in ./tests/ directory.
# The tests must be in the following format: test$x.in test$x.ok

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

for testfile in `find tests -name "test*.in" | sort -V`; do
    touch out

    runtime_error=1
    runtime=`(TIMEFORMAT='%3R'; time ./mlc < $testfile > out) 2>&1`
    if [ "${#runtime}" = "5" ]; then
        runtime_error=0
    fi

    ok=`echo $testfile | cut -d \. -f 1 | cut -d \/ -f 2`
    ok="tests/${ok}.ok"

    testnumber=`echo $testfile | sed 's/[^0-9]//g'`

    if [ $runtime_error != 0 ]; then
        message="Test ${testnumber} | 0.000 | Runtime Error"
    else
        dwdiff out $ok > /dev/null
        if [ $? != 0 ]; then
            message="Test ${testnumber} | ${runtime} | Wrong Answer"
        else
            message="Test ${testnumber} | ${runtime} | Correct"
        fi
    fi

    echo $message
    rm out
done

rm mlc
