# Assignment 1: Introduction to System Calls and Processes

## Objective
Learn basic system calls and process creation in Unix/Linux systems.

## Description
This assignment introduces fundamental concepts of process management:
- Process creation using `fork()`
- Process identification with `getpid()` and `getppid()`
- Process execution using `exec()` family of functions
- Process termination and waiting with `wait()` and `waitpid()`

## Tasks
1. Create a simple program that forks a child process
2. Have the parent and child print their respective PIDs
3. Demonstrate proper process synchronization using `wait()`

## Files
- `process_example.c` - Example program demonstrating process creation
- `Makefile` - Build configuration

## Building
```bash
make
```

## Running
```bash
./process_example
```

## Expected Output
The program should display parent and child process IDs and demonstrate proper process creation and termination.

## Submission Guidelines
- Ensure code compiles without warnings
- Test thoroughly before submission
- Document any assumptions or design decisions
