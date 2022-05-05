// project_1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
/*
#include<stdio.h>
#include<mpi.h>
#include<string.h>

*/
/*
int main() {
	int my_rank, comm_sz;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	printf("%d and %d fine", my_rank, comm_sz);
	MPI_Finalize();
	return 0;
}*/
/*
const int MAX_STRING = 100;
int main() {
	char greet[MAX_STRING];
	int comm_sz;
	int my_rank;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	if (my_rank != 0) {
		sprintf(greet, "hell test%d and %d", my_rank, comm_sz);
		MPI_Send(greet, strlen(greet) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
	}
	else {
		printf("greet from %d and %d", my_rank, comm_sz);
		for (int i = 0;i < comm_sz;i++) {
			MPI_Recv(greet, MAX_STRING, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
			printf("%s\n", greet);
		}
	}
	MPI_Finalize();
	return 0;*/
	/*
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
			printf("接收到第%d号进程发送的消息：%s\n", source, message);
		}
	}
	MPI_Finalize();
	
}*/
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
