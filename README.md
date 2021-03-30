# Threaded-Matrix
It is a multi-threaded matrix multiplication program.  
The input to the program is two matrixes A(x*y) and B(y*z) that are read from corresponding files.  
The output is a matrix C(x*z) that is written to an output file.  
User should determine his files' path or program will use the default ones which are **a.txt, b.txt & c.txt** in src folder.  

A parallelized version of matrix multiplication can be done using one of these two methods:  
**1. a thread computes each row in the output C matrix.  
2. a thread computes each element in the output C matrix.**  
The progtam performs the multiplication using the two implementations then compares according to:
the number of thread created and the execution time taken.



