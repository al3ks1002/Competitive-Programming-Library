#!/bin/bash

# Tests your source code against some tests.
# The tests must be in the following format: test$x.in test$x.ok

# Color codes for colored echo.
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

# Function needed to show the usage.
usage() {
    printf "${RED}Usage -s source_file -t tests_directory [-c checker].${NC}\n"
    exit 1
}

# Checks if a parameter is empty.
# $1 = a string that will be printed.
# $2 = the name of the file.
check_not_empty() {
    string=$1
    file=$2
    if [[ -z $file ]]; then
        printf "${RED}$string argument is mandatory.${NC}\n"
        usage
        exit 1
    fi
}

# Checks if a file exists.
# $1 = a string that will be printed.
# $2 = the name of the file.
check_if_exists() {
    string=$1
    file=$2
    if [[ ! -e $file ]]; then
        printf "${RED}$file: $string does not exist.${NC}\n"
        exit 1
    fi
}

# Checks if a file is a directory.
# $1 = a string that will be printed.
# $2 = the name of the directory.
check_if_directory() {
    string=$1
    dir=$2
    if [[ ! -d $dir ]]; then
        printf "${RED}$dir: $string is invalid.${NC}\n"
        exit 1
    fi
}

# Compiles a C++ file.
# $1 = the source file.
# $2 = the name of the executable.
compile() {
    source=$1
    executable=$2
    g++ -w -std=c++14 -O2 -o $executable $source
    if (( $? != 0 )); then
        printf "${RED}$source: Compilation error.${NC}\n"
        exit 1
    fi
}

# Runs a test.
run_test() {
    # $input represents the input file.
    input=$1

    # Gets the test number.
    testnumber=$(echo $input | rev | cut -d / -f 1 | sed 's/[^0-9]//g' | rev)

    # $output represents the output file generated by the source file.
    output=test${testnumber}.out
    touch $output

    # Runtime error flag.
    runtime_error=0

    # Gets the CPU runtime in format "x.xxx".
    runtime=$( (TIMEFORMAT='%3R'; time ./sourcefile_exec < $input > $output) 2>&1)

    # If the length of the runtime doesn't have 5 characters, there is a runtime error.
    if [[ "${#runtime}" != "5" ]]; then
        runtime_error=1
    fi

    # Gets the ok file.
    ok=$(echo $input | rev | sed s/ni/ko/1 | rev)

    # If the test number is < 10, it adds a leading 0 (helps with the indentation).
    if (( testnumber < 10 )); then
        testnumber="0$testnumber"
    fi

    # If there is a runtime error, gets the runtime error message.
    if [[ $runtime_error != 0 ]]; then
        message="${RED}Test $testnumber | 0.000 | Runtime Error"
    else
        # Checks if the checker exists.
        if [[ -z $checker ]]; then
            # If not, does a word diff between the output file and the ok file.
            dwdiff $output $ok > /dev/null

            # Gets the message based on the diff.
            if [[ $? != 0 ]]; then
                message="${RED}Test $testnumber | $runtime | Wrong Answer"
            else
                message="${GREEN}Test $testnumber | $runtime | Correct"
            fi
        else
            # If yes, runs the checker.
            # The checker should print to stdout the result and exit with a code.
            # 0 - okay;
            # 1 - wrong;
            # 2 - something went bad when running the checker (probably the args were invalid).
            result=$(./checker_exec $input $output $ok)

            # Gets the message based on the checker exit code.
            if [[ $? == 0 ]]; then
                message="${GREEN}Test $testnumber | $runtime | $result"
            else
                message="${RED}Test $testnumber | $runtime | $result"
            fi
        fi
    fi

    # Prints the test result.
    printf "$message${NC}\n"

    # Cleans the output.
    rm $output
}

main() {
    # Parses the parameters.
    while getopts ":s:t:c:" opt; do
        case $opt in
            s)
                # Gets the source file.
                sourcefile=$OPTARG
                ;;
            t)
                # Gets the tests directory.
                tests=$OPTARG
                ;;
            c)
                # Gets the checker file.
                checker=$OPTARG
                ;;
            \?)
                printf "${RED}Invalid option: -$OPTARG.${NC}\n" >&2
                usage
                ;;
            :)
                printf "${RED}Option -$OPTARG requires an argument.${NC}\n" >&2
                usage
                ;;
        esac
    done

    # Checks if the source file and tests directory are not empty.
    check_not_empty "Source file" $sourcefile
    check_not_empty "Tests directory" $tests

    # Checks if the source file exists.
    check_if_exists "Source file" $sourcefile

    # Checks if the test directory is valid.
    check_if_directory "Tests directory" $tests

    # Compiles the source file.
    compile $sourcefile "sourcefile_exec"

    # Checks if the checker exists.
    if [[ ! -z $checker ]]; then
        # Checks if the checker file exists.
        check_if_exists "Checker" $checker

        # Compiles the checker file.
        compile $checker "checker_exec"
    fi

    # Goes through all the tests sorted numerically and runs the source file on them.
    for input in $(find $tests -name "test*.in" | sort -V); do
        run_test $input
    done

    # Cleans the executable files.
    rm sourcefile_exec
    rm checker_exec 2> /dev/null
}

# Run main with all the parameters given to the script.
main "$@"
