# Competitive-Programming-Library

A C++ library designed for usage in competitive programming.

Every algorithm/data structure has two directories:
* a directory containing implementations and the description of the problem that is being solved;
* a directory containing tests (with potentially generators or checkers).

The tests are taken from [infoarena](http://www.infoarena.ro/) or are generated randomly (you also have a generator for those).

If you want to modify or create your own implementation for an algorithm you can verify the correctness and the CPU time with "run.sh" or "easy-run.sh" scripts. You will need [dwdiff](https://linux.die.net/man/1/dwdiff) for comparing output and [gnusort](http://superuser.com/questions/349897/ls-version-number-sorting-mac-os-x/349904#349904) for sorting the tests. If you don't have gnusort, your tests will still be evaluated, but not in order. If you get an error regarding -std=c++14, just upgrade your g++.

There are some scripts that you can use:
* "run.sh" - takes as arguments the source file (-s), the tests directory (-t) and optionally the checker (-t); example usage: ./run.sh -s my-source-file.cpp -d my-tests-directory/ -c my-checker.cpp;
* "easy-run.sh" - shows you a menu with all the available sources from src/ directory and gives you the option to run one of them based on an index; takes as arguments the apparition of the menu (-m <0/1>) and the index (-i); example usage: ./easy-run.sh -m 0 -i 23; if you want to use this script, you need to leave the structure of the repository as it is;
* "menu.sh" - shows you the source file menu (so that you can grep on it to find the source that you're interested in).
