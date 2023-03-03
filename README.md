# C++ Output Benchmark (in competitive programming)

This repository contains a benchmarking test for the common ways to output in C++ competitive programming.

Tests included:
- Simple Data Output (single number / single string)
  - `std::cout` without special settings.
  - `std::printf`.
  - Fast write algorithms that are widely-used by competitive programmers.
  - `std::cout` with `ios_base::sync_with_stdio(false)`.
  - `std::cout` with `ios_base::sync_with_stdio(false)` and `std::cout.tie(0)`, `std::cin.tie(0)`.
- Compound Data Output
  - `std::cout` without special settings.
  - `std::printf`.
  - `std::cout` with `ios_base::sync_with_stdio(false)`.

## Getting Started

To run the benchmarking, you need the following tools:
- `zsh >= 5.8.1`
- Any C++ compiler that is compatible with `g++` (i.e. having the same command-line options), the compiler should support at least C++14 and aliased/symlinked to `g++`. (If you don't want to alias/symlink it to `g++`, you can also change the content of the variable `CXX` in the `makefile` to your compiler's path. )
- `make >= 3.81`
- A system that supports `/` as the path separator and having a modern file system.

In order to start the benchmarking, you simply run:
```shell
./launch_test
```
By default, the `stderr` (where the result stays) will be redirected to `report/result.txt` and an additional output `stdout` will be redirected to `report/test.log` for you to check some internal details like checking if the timer overflowed, etc. Usually the code is well-tested and you just need to care about the pretty final result in the `report/result.txt`. Since one test may be repeated for many times in order to get a more accurate result, the `report/test.log` usually contains thousands of lines. Thus, if you don't want the `report/test.log` to appear, you can run the `./launch_test` script with an additional argument:
```shell
./launch_test --no-outlog
```
If you can't execute the `./launch_test` script but you checked your environment are correct (matching the description at the start of this section), you can try this to see if it works or not.
```shell
chmod a+x ./launch_test
```
If it doesn't work either, please create a new issue and describe the problem as detailed as possible.
