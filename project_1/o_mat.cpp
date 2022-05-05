#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
int main_00(int argc, char* argv[]) {
	double start, end;

	start = omp_get_wtime();

	int numprocs = strtol(argv[1], NULL, 10);

	int i,n,j,m;

	printf("input m n \n");

	scanf("%d%d", &m, &n);

	int** A = (int**)malloc(m * sizeof(int*));

	int* x = (int*)malloc(n * sizeof(int));

	int* y = (int*)malloc(m * sizeof(int));

	printf("mat=\n");

	for (i = 0;i < m;i++) {
		
		A[i] = (int*)malloc(n * sizeof(int));

		for (j = 0;j < n;j++) {

			A[i][j] = rand() % (5 + j);

			printf("%d ", A[i][j]);

		}

		printf("\n");

	}

	printf("x=\n");

	for (j = 0;j < n;j++) {

		x[j] = rand() % (4 + j);

		printf("%d ", x[j]);

	}
#	pragma omp parallel for num_threads(numprocs)\
		default(none) private(i,j) shared(A,x,y,m,n)

	for(i = 0;i < m;i++){

		y[i] = 0;

		for (j = 0;j < n;j++)

			y[i] += A[i][j] * x[j];

	}

	printf("\n");

	printf("y=\n");

	for (i = 0;i < m;i++) {

		printf("%d ", y[i]);

		}
	
	end = omp_get_wtime();
	
	printf("\nrun time %lf s", end - start);

	return 0;
}