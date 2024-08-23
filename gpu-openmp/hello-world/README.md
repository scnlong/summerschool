# Hello world with OpenMP offloading

Compile and run a simple OpenMP test program, provided as `hello(.c|.F90)`.
Examples of batch scripts for GPUs and CPUs can be found in
[../../exercise-instructions.md](exercise-instructions.md)

1. Compile the program first without offloading support. you will need
   ```
   source ../modules-cpu
   ```
   Try to run the code in a CPU and GPU node.

2. Next, compile the code with offloading support.
   ```
   source ../modules-gpu
   ```
   Try to run both in a GPU node and in a CPU node.
