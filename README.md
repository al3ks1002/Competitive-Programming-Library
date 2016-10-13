# Library-for-Competitive-Programming

A C++ library designed for usage in competitive programming.

Every algorithm/data structure has a special folder containing implementations, tests and the description of the problem that is being solved.

The tests are taken from [infoarena](http://www.infoarena.ro/) or are generated randomly (you also have a generator for those).

If you want to modify or create your own implementation for an algorithm you can verify the correctness and the CPU time with "test.sh" script. You will need [dwdiff](https://linux.die.net/man/1/dwdiff) for comparing output and [gnusort](http://superuser.com/questions/349897/ls-version-number-sorting-mac-os-x/349904#349904) for sorting the tests. If you don't have gnusort, you can just remove -V flag from the script (sort -V).
