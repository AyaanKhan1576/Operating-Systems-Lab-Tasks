# Lab 08

This folder contains C programs demonstrating various overflow vulnerabilities and process management for Operating Systems Lab 08.

## Files
- `data_overflow.c`: Data overflow example.
- `fork_bomb.c`: Fork bomb example.
- `heap_overflow.c`: Heap overflow example.
- `main.c`: Main program.
- `stack_overflow.c`: Stack overflow example.

## How to Use
Compile each C file using GCC, for example:

```bash
gcc data_overflow.c -o data_overflow
gcc fork_bomb.c -o fork_bomb
gcc heap_overflow.c -o heap_overflow
gcc main.c -o main
gcc stack_overflow.c -o stack_overflow
```

Run the executables as needed. **Warning:** Some programs (like fork bombs or overflows) may crash your system. Use with caution.
