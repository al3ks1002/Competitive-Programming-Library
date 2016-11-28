#!/bin/bash

# This script helps you run a source file faster than with the run.sh script.
# With the run.sh script you had to write all the arguments (source file, tests dir, checker).
# In easy-run.sh you just choose the source file from a list and the script does the rest.

# !! If you want to use this, you need to leave the repository structure as it is.

# Color codes for colored echo.
RED='\033[0;31m'
GREEN='\033[0;32m'
ORANGE='\033[0;33m'
PURPLE='\033[0;35m'
NC='\033[0m'

# Function needed to show the usage.
usage() {
    # -m stands for the menu: 1 - show menu, 0 - don't show.
    # -i stands for the source file index that you need to run.
    printf "${RED}Usage [-m <0/1>] [-i index].${NC}\n"
    exit 1
}

# Reads the index from the keyboard.
get_user_index() {
    while true; do
        printf "\n${GREEN}Choose an index: ${NC}"
        read user_index

        if [[ ! $user_index =~ ^[0-9]+$ ]] || ((user_index >= index)); then
            printf "${RED}Invalid index.${NC}\n"
        else
            break
        fi
    done
}

# Runs the program with a given index and source file.
run_program() {
    # Gets the index.
    user_index=$1

    # Gets the source file.
    source_file=$2

    printf "${PURPLE}Running: [$user_index] $source_file${NC}\n"

    # Gets the path.
    path=$(echo $source_file | rev | cut --complement -d / -f 1 | rev)

    # Gets the test directory.
    tests_dir=$(echo $path | sed 's/src/tests/1')

    # Gets the checker file.
    checker="${tests_dir}/checker.cpp"

    # Builds the command that runs run.sh.
    command="./run.sh -s $source_file -t $tests_dir"

    # If the checker exists, adds the checker to the command.
    if [[ -e $checker ]]; then
        command="${command} -c $checker"
    fi

    # Runs the source file.
    eval $command
}

main() {
    # By default, the menu is on.
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
                printf "${RED}Invalid option: -$OPTARG${NC}\n" >&2
                usage
                ;;
            :)
                printf "${RED}Option -$OPTARG requires an argument.${NC}\n" >&2
                usage
                ;;
        esac
    done

    # $index will represent the max number of source files.
    index=0

    # Gets all the source files.
    for file in $(find ../src -name "*.cpp" | sort); do
        if (( $menu != 0 )); then
            printf "${ORANGE}[$index] $file${NC}\n"
        fi
        ((++index))
    done

    # Gets the user index.
    if [[ -z $user_index ]]; then
        user_index=$index
        get_user_index
    else
        if [[ ! $user_index =~ ^[0-9]+$ ]] || ((user_index >= index)); then
            printf "${RED}Invalid index.${NC}\n"
            get_user_index
        fi
    fi

    # Finds the source file matches with the user index and runs it in "run_program" function.
    index=0
    for file in $(find ../src -name "*.cpp" | sort); do
        if ((index == user_index)); then
            run_program $user_index $file
            break
        fi
        ((++index))
    done
}

# Runs main with the script arguments.
main "$@"
