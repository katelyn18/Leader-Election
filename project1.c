/*
Katelyn Jaing
Melissa Riddle
Hector Medina
CPSC 479-01
Project 1: Concurrent two leader election algorithm
*/

#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>
int main(int argc, char *argv[])   { 
	int temp, rank, size;
	int num[ 2 ];
    MPI_Init(&argc,&argv);     
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);    
    MPI_Comm_size(MPI_COMM_WORLD,&size); 
	srand( time( NULL ) + rank );

	if( ( size < 5 || size > 20 ) && rank == 0 ){
		printf( "Error: N must be greater than 5 but less than 20\n" );
		MPI_Abort( MPI_COMM_WORLD, 1 );
	}
	else if( rank != 0 ){
		MPI_Recv( &num, 2, MPI_INT, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE );
		printf( "Process %d received even %d odd %d from process %d\n", rank, num[ 0 ], num[ 1 ], rank-1 ); 

		temp = rand();

		if( temp > 100 ){
			temp %= 100;
		}
		else if( temp < 10 ){
			temp += 10;
		}

		int t = ( rank * 100 ) + 1000;
		temp += t; 

		if( temp % 2 == 0 ){
			if( temp > num[ 0 ] ){
				num[ 0 ] = temp;
			}
		}
		else{
			if( temp > num[ 1 ] ){
				num[ 1 ] = temp;
			}
		}

		MPI_Send( &num, 2, MPI_INT, (rank+1)%size, 0, MPI_COMM_WORLD );
		if( rank != size-1 ){
			printf( "Process %d sent even %d odd %d to process %d\n", rank, num[ 0 ], num[ 1 ], rank+1 );
		}
		else{
		printf( "Process %d sent even %d odd %d to process 0\n", rank, num[ 0 ], num[ 1 ] ); 
		}
	}
	else{
		temp = rand();

		if( temp > 100 ){
			temp %= 100;
		}
		else if( temp < 10 ){
			temp += 10;
		}
	
		//concatenate
		temp += 1000;

		if( temp % 2 == 0 ){
			num[ 0 ] = temp;
			num[ 1 ] = 1;
		}
		else{
			num[ 0 ] = 0;
			num[ 1 ] = temp;
		}
		MPI_Send( &num, 2, MPI_INT, (rank+1)%size, 0, MPI_COMM_WORLD );
		printf( "Process 0 sent even %d odd %d to process %d\n", num[ 0 ], num[ 1 ], rank+1 );
	}

	if( rank == 0 ){
		MPI_Recv( &num, 2, MPI_INT, size-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE );
		printf( "Process 0 received even %d odd %d from process %d\n", num[ 0 ], num[ 1 ], size-1 ); 
		printf( "President: %d, Vice President: %d\n", num[ 0 ], num[ 1 ] );
	}


	MPI_Finalize();    
    return 0;
}

