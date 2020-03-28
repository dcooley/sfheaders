
* updates v0.1.0 to v0.2.2
* skipping over v0.2.1

## clang and gcc UBSAN errors

The previous version found

>   clang-UBSAN
> <https://www.stats.ox.ac.uk/pub/bdr/memtests/clang-UBSAN/sfheaders>
>   gcc-UBSAN
> <https://www.stats.ox.ac.uk/pub/bdr/memtests/gcc-UBSAN/sfheaders>

> sfheaders.Rcheck/tests/testthat.Rout:/usr/include/c++/9/bits/stl_vector.h:1043:34:
runtime error: reference binding to null pointer of type 'value_type'
> sfheaders.Rcheck/tests/testthat.Rout:/usr/local/bin/../include/c++/v1/vector:1549:12:
runtime error: reference binding to null pointer of type 'long'


These were due to me incorrectly using a 'long' to index a vector, where I should have used 'int'. This has been fixed in [this commit](https://github.com/dcooley/sfheaders/commit/4b0514bfe3df45a0de9b4c6f71804d638d95c7f2#diff-7a5d477089d3ceb79e115d2dde0cfef0)

Checked with `rhub::check_with_sanitizers()` and `rhub::check_for_cran()`



## Test environments

* local OS X install, R 3.6.1
* ubuntu 14.04 (on travis-ci), R 3.5.0
* rub checks for cran with sanitizers
* win-builder (devel and release)
