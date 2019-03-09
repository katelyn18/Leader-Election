# Leader-Election
This program uses MPI and an algorithm to "elect" a President and Vice President. 
Each process will generate a random value and concatenate 1 plus the process rank to the beginning of the value. If the new value is an even number, an odd value of 1 will be created. If the new value is an odd number, an even value of 0 will be created. Even numbers will be compared to even numbers and odd numbers with odd numbers. The highest even and odd number will be taken. At the end, the President will be the highest even value and the Vice President will be the highest odd value. <br />
To run the code: (N is the number of processors, which will be greater than 5 but less than 20) <br />
  mpicc [filename] <br />
  mpirun -n N ./a.out
