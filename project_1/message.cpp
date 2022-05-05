/*
#include<stdio.h>
#include<mpi.h>
#include<string.h>
int main() {
	int numprocs, myid, source;
	MPI_Status status;
	char message[100];
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	if (myid != 0) {  //非0号进程发送消息
		strcpy(message, "Hello World!");
		MPI_Send(message, strlen(message) + 1, MPI_CHAR, 0, 99,
			MPI_COMM_WORLD);
	}
	else {   // myid == 0，即0号进程接收消息
		for (source = 1; source < numprocs; source++) {
			MPI_Recv(message, 100, MPI_CHAR, source, 99,
				MPI_COMM_WORLD, &status);
			printf("Hello, I'm process %d\n", source);
		}
	}
	MPI_Finalize();
	return 0;
}*/