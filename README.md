# Banker's Algorithm in C++

Explanation: https://www.youtube.com/watch?v=T0FXvTHcYi4

Input format:

```py
3 5              # types of resources, number of processes
10 5 7           # resource instance per type of resource
P0 0 1 0 7 5 3   # first column: process name
P1 2 0 0 3 2 2   # 2nd to n+1th column, allocated resources per type
P2 3 0 2 9 0 2   # n+2th to n+5th column, max resource per type
P3 2 1 1 2 2 2   
P4 0 0 2 4 3 3   # you can think of the remaining columns after the name as two halves
```

## Compiling

When compiling for the first time, you can run

```bash
make    # this also executes the program with `input.txt` as its argument.
```

or

```
g++ -o lada lada.cpp
```

## Running

The input file is to be provided as an argument to the executable.

```bash
./lada input.txt    # succeeding case
./lada fail.txt     # failing case
```
