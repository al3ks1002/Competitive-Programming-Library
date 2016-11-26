#!/bin/bash

# Color codes for colored echo.
RED='\033[0;31m'
GREEN='\033[0;32m'
ORANGE='\033[0;33m'

# Function needed to show the usage.
usage() {
    echo "Usage [-m <0/1>] [-i index]."
    exit 1
}

get_user_index() {
    while true; do
        printf "\n${GREEN}Choose an index: "
        read user_index

        if ((user_index < 0 || user_index >= index)); then
            printf "${RED}Invalid index.\n"
        else
            break
        fi
    done
}

run_program() {
    user_index=$1
    source_file=$2
    printf "${GREEN}Running: [$user_index] $source_file\n"
    path=$(echo $source_file | rev | cut --complement -d / -f 1 | rev)
    tests_dir=$(echo $path | sed 's/src/tests/1')
    checker="${tests_dir}/checker.cpp"
    command="./run.sh -s $source_file -t $tests_dir"
    if [[ -e $checker ]]; then
        command="${command} -c $checker"
    fi
    eval $command
}

menu=1

# Parses the parameters.
while getopts ":m:i:" opt; do
    case $opt in
        m)
            # Gets the source file.
            menu=$OPTARG
            ;;
        i)
            # Gets the tests directory.
            user_index=$OPTARG
            ;;
        \?)
            echo "Invalid option: -$OPTARG" >&2
            usage
            ;;
        :)
            echo "Option -$OPTARG requires an argument." >&2
            usage
            ;;
    esac
done

index=0
for file in `find ../src -name "*.cpp"`; do
    if (( $menu != 0 )); then
        printf "${ORANGE}[$index] $file\n"
    fi
    ((++index))
done

if [[ -z $user_index ]]; then
    user_index=-1
    get_user_index
else
    if ((user_index < 0 || user_index >= index)); then
        printf "${RED}Invalid index.\n"
        get_user_index
    fi
fi

index=0
for file in `find ../src -name "*.cpp"`; do
    if ((index == user_index)); then
        run_program $user_index $file
        break
    fi
    ((++index))
done

