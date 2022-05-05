//#include<stdio.h>
//#include<omp.h>
//#include<stdlib.h>
//
//int main(int argc, char* argv[]) {
//	
//	double start, end;
//	
//	start = omp_get_wtime();
//
//	int numprocs, n, i, tmp, phase;
//
//	numprocs = strtol(argv[1], NULL, 10);
//
//	printf("input n\n");
//
//	scanf("%d", &n);
//
//	int* arr = (int*)malloc(n * sizeof(int));
//
//	for (i = 0;i < n;i++) {
//
//		arr[i] = rand() % (30 + i);
//
//		//printf("%d ", arr[i]);
//
//	}
//
//# pragma omp parallel num_threads( numprocs) \
//default(none) shared(arr,n) private( i,tmp, phase)
//
//	for (phase = 0; phase < n; phase++) {
//		if (phase % 2 == 0)
//
//#			pragma omp for
//
//			for (i = 1;i < n;i += 2) {
//
//				if (arr[i - 1] > arr[i]) {
//
//					tmp = arr[i - 1];
//
//					arr[i - 1] = arr[i];
//
//					arr[i] = tmp;
//
//				}
//			}
//	else
//
//#			pragma omp for
//
//			for (i = 1;i < n - 1;i += 2) {
//
//				if (arr[i] > arr[i + 1]) {
//
//					tmp = arr[i + 1];
//
//					arr[i + 1] = arr[i];
//
//					arr[i] = tmp;
//
//				}
//
//			}
//	}
//	printf("\n");
//
//	//for (i = 0;i < n;i++)
//
//		//printf("%d ", arr[i]);
//
//	end = omp_get_wtime();
//
//	printf("\nrun time %lf s", end - start);
//
//	return 0;
//
//}