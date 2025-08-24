# xv6 System Call: getparentname

This project adds a new system call `getparentname` to the xv6 operating system that retrieves the names of the current process and its parent process.

## Overview

The `getparentname` system call allows user programs to obtain the names of both the current process and its direct parent process. This can be useful for debugging, process monitoring, and understanding process relationships within the xv6 operating system.

## System Call Signature

```c
int getparentname(char* parent_name, char* child_name, int parent_buf_len, int child_buf_len);
```

### Parameters:
- `parent_name`: Buffer to store the parent process name
- `child_name`: Buffer to store the current process name  
- `parent_buf_len`: Length of the parent name buffer
- `child_buf_len`: Length of the child name buffer

### Return Value:
- Returns 0 on success
- Returns -1 on error (invalid pointers or insufficient buffer size)

## Files Modified

The implementation required changes to several xv6 source files:

1. **sysproc.c** - Added system call implementation
2. **user.h** - Added user-space function prototype
3. **getparentname.c** - User-space wrapper function
4. **usys.S** - Added system call entry
5. **syscall.h** - Added system call number
6. **syscall.c** - Registered system call handler
7. **Makefile** - Added compilation rules

## Test Cases

Three comprehensive test cases are included:

### Test 1: Basic Functionality
- Verifies that `getparentname` correctly returns both parent and child process names
- Expected output shows the relationship between init process and the test process

### Test 2: Null Pointer Handling
- Tests error handling when null pointers are passed as buffer arguments
- Ensures the system call returns -1 and doesn't crash

### Test 3: Zero Buffer Length Handling
- Tests error handling when buffer lengths of 0 are provided
- Verifies proper error return for insufficient buffer sizes

## Building and Running

### Prerequisites
- xv6 operating system environment
- QEMU emulator
- GCC cross-compiler for xv6

### Building
```bash
make
```

### Running Tests
```bash
./run-tests.sh
```

### Test Options
- `-h` - Show help message
- `-v` - Verbose output
- `-t n` - Run only test n
- `-c` - Continue after failures
- `-d testdir` - Use alternative test directory
- `-s` - Skip pre-test initialization

## Adding New Tests

To add new test cases:

1. Create `test_n.c` in the `tests/tests/` directory
2. Add corresponding `n.rc`, `n.out`, and `n.err` files
3. Update the `pre` file to include the new test
4. Run tests with `./run-tests.sh -t n` to verify

## Implementation Details

The system call works by:
1. Validating pointer arguments and buffer sizes
2. Copying process names from the current process and its parent
3. Ensuring proper null-termination of strings
4. Handling edge cases and error conditions gracefully

## Status

All three provided test cases pass successfully, demonstrating correct functionality and robust error handling.
