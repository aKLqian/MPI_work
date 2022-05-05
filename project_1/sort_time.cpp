#include<stdio.h>
#include<mpi.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>
void Merge_lo(
	int my_keys[],
	int recv_keys[],
	int temp_keys[],
	int local_n) {
	int m_i, r_i, t_i;
	m_i = r_i = t_i = 0;
	while (t_i < local_n) {
		if (my_keys[m_i] <= recv_keys[r_i]) {
			temp_keys[t_i] = my_keys[m_i];
			t_i++; m_i++;
		}
		else {
			temp_keys[t_i] = recv_keys[r_i];
			t_i++; r_i++;
		}
	}
	for (m_i = 0; m_i < local_n; m_i++) {
		my_keys[m_i] = temp_keys[m_i];
	}
}
void Merge_hig(
	int my_keys[],
	int recv_keys[],
	int temp_keys[],
	int local_n) {
	int m_i, r_i, t_i;
	m_i = r_i = t_i = local_n - 1;
	while (t_i >= 0) {
		if (my_keys[m_i] >= recv_keys[r_i]) {
			temp_keys[t_i] = my_keys[m_i];
			t_i--; m_i--;
		}
		else {
			temp_keys[t_i] = recv_keys[r_i];
			t_i--; r_i--;
		}
	}
	for (m_i = 0; m_i < local_n; m_i++)
	{
		my_keys[m_i] = temp_keys[m_i];
	}
}
int compp(const void* a, const void* b)
{
	return *(int*)a - *(int*)b;
}

int man_1() {
	
	srand(time(0));

	int numprocs, myid;

	double start, finish;

	MPI_Status status;

	MPI_Init(NULL, NULL);

	start = MPI_Wtime();

	MPI_Comm_rank(MPI_COMM_WORLD, &myid);

	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

	int n, phase, partner, i;

	int* arr = NULL, * x = NULL, * recv = NULL, * temp = NULL;

	if (myid == 0) {

		printf("input the size of arrny");

		scanf("%d", &n);

		if (n % numprocs != 0)exit(0);

		x = (int*)malloc(n * sizeof(int));

	}

	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

	int local_len = n / numprocs;

	arr = (int*)malloc(local_len * sizeof(int));

	temp = (int*)malloc(local_len * sizeof(int));

	recv = (int*)malloc(local_len * sizeof(int));

	/*生成随机数组*/
	for (i = 0;i < local_len;i++) {

		arr[i] = rand() % (30 + myid + i);

		//srand(time(0));

	}
	/*数组发送至0进程打印*/
	MPI_Gather(arr, local_len, MPI_INT, x, local_len, MPI_INT, 0, MPI_COMM_WORLD);

	if (myid == 0) {
		printf("arr=");

		for (i = 0;i < n;i++)printf("%d ", x[i]);

		printf("\n");
	}
	/*进程通信*/
	for (phase = 0;phase < numprocs;phase++) {
		/*伙伴进程*/

		if (phase % 2 == 0)
			if (myid % 2 != 0)partner = myid - 1;

			else partner = myid + 1;
		else
			if (myid % 2 != 0)partner = myid + 1;

			else partner = myid - 1;
		if (partner == -1 || partner == numprocs)

			partner = MPI_PROC_NULL;
		/*内部排序*/
		qsort(arr, local_len, sizeof(int), compp);

		MPI_Sendrecv(arr, local_len, MPI_INT, partner, 0,
			recv, local_len, MPI_INT, partner, 0, MPI_COMM_WORLD, &status);
		if (partner != MPI_PROC_NULL)
			if (myid < partner)
				Merge_lo(arr, recv, temp, local_len);
			else
				Merge_hig(arr, recv, temp, local_len);
	}
	/*数组聚集*/
	MPI_Gather(arr, local_len, MPI_INT, x, local_len, MPI_INT, 0, MPI_COMM_WORLD);

	if (myid == 0) {
		printf("\nsorted arr=");

		for (i = 0;i < n;i++)printf("%d ", x[i]);

		printf("\n");
	}

	finish = MPI_Wtime();

	MPI_Finalize();

	printf("%d proc time = %e s\n", myid, finish - start);

	return 0;
}