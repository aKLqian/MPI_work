#include<stdio.h>
#include<mpi.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
int man() {
	srand(time(0));

	int er = 0;

	int i, j;

	int numprocs, myid;

	MPI_Status status;

	int m, n;

	int* A = NULL;

	int* ans = NULL;

	int* big_x = NULL;

	MPI_Init(NULL, NULL);

	MPI_Comm_rank(MPI_COMM_WORLD, &myid);

	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

	MPI_Aint mmm, nnn;

	MPI_Get_address(&n, &nnn);

	MPI_Get_address(&m, &mmm);

	int arr_1[] = { 1,1 };

	MPI_Aint arr_2[] = { 0,mmm - nnn };

	MPI_Datatype arr_3[] = { MPI_INT,MPI_INT };

	MPI_Datatype newname;

	MPI_Type_create_struct(2, arr_1, arr_2, arr_3, &newname);

	MPI_Type_commit(&newname);

	/*生成随机矩阵*/
	if (myid == 0) {
		printf("input m n\n");

		do {
			scanf("%d%d", &m, &n);

			if (er++ > 3 ) {
				
				exit(0);

				MPI_Type_free(&newname);

				MPI_Finalize();

				return 0;
			}

			if (m % numprocs == 0 && n % numprocs == 0)break;

			printf("error input\n");

		} while (1);

		A = (int*)malloc(m * n * sizeof(int));

		for (i = 0;i < m * n;i++)
			A[i] = rand() % 10;

		ans = (int*)malloc(m * sizeof(int));

	}
	MPI_Bcast(&n, 1, newname, 0, MPI_COMM_WORLD);

	big_x = (int*)malloc(m * sizeof(int));

	int little_len = m / numprocs;

	/*将矩阵分发到每个进程*/

	int* a = (int*)malloc(n * little_len * sizeof(int));

	int* as = (int*)malloc(little_len * sizeof(int));

	MPI_Scatter(A, little_len * n, MPI_INT, a, little_len * n, MPI_INT, 0, MPI_COMM_WORLD);

	/*每个进程随机生成x的分量*/

	int* x = NULL;

	x = (int*)malloc(little_len * sizeof(int));

	for (i = 0;i < little_len;i++) {

		x[i] = rand() % 10;

	}
	/*发送x向量*/

	MPI_Allgather(x, little_len, MPI_INT, big_x, little_len, MPI_INT, MPI_COMM_WORLD);

	/*矩阵相乘*/
	for (i = 0;i < little_len;i++) {

		as[i] = 0;

		for (j = 0;j < n;j++) {

			as[i] += a[n * i + j] * big_x[j];

		}

	}
	/*结果发回*/
	//MPI_Reduce(as, ans, m, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	MPI_Gather(as, little_len, MPI_INT, ans, little_len, MPI_INT, 0, MPI_COMM_WORLD);

	if (myid == 0) {
		printf("A=\n");

		for (i = 0;i < m;i++) {

			for (j = 0;j < n;j++)

				printf("%d ", A[i * n + j]);

			printf("\n");
		}
		printf("x=");

		for (i = 0;i < n;i++)printf("%d ", big_x[i]);

		printf("\nans=\n");

		for (i = 0;i < m;i++) {

			printf("%d ", ans[i]);

		}
	}
	printf("\n");

	MPI_Type_free(&newname);

	MPI_Finalize();

	return 0;
}