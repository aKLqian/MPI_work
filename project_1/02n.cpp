/*#include<stdio.h>
#include<mpi.h>
#include<string.h>
int main() {
	int numprocs, myid;
	MPI_Status status;
	char message[100];
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	if (myid != 0) {
		MPI_Recv(message, 100, MPI_CHAR, myid - 1,0,MPI_COMM_WORLD, &status);
		printf("%s\n",message);
	}
	if (myid != numprocs-1) {
		sprintf(message, "Hello, I'm process %d", myid);
		MPI_Send(message, strlen(message) + 1, MPI_CHAR, myid + 1, 0, MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}*/