# Multithreaded Matrix Multiplication Engine in C

This project implements a high-performance matrix multiplication engine using POSIX threads in C. It demonstrates memory management, concurrency, and time-optimized computation.

## Features

- Dynamic memory allocation
- Clean separation of thread logic
- Performance benchmarking
- Scalable for matrices up to 1024x1024
- Portable and standards-compliant

## How to Compile and Run

```bash
gcc -pthread -O2 matrix_multithreaded.c -o matrix_engine
./matrix_engine
