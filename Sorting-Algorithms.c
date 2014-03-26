#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double* insertArray;
double* cocktailArray;
double* quickArray;
int size;

/*
 * QUICKSORT
 */
void medianOf3(double *arr, int L, int R) {
	int temp;
	int center;
	center = (L+R)/2;
	if (arr[L] > arr[center]) {
		temp = arr[L];
		arr[L] = arr[center];
		arr[center] = temp;
	}
	if (arr[R] < arr[L]) {
		temp = arr[R];
		arr[R] = arr[L];
		arr[L] = temp;
	}
	if (arr[center] > arr[R]) {
		temp = arr[center];
		arr[center] = arr[R];
		arr[R] = temp;
	}
	temp = arr[center];
	arr[center] = arr[R];
	arr[R] = temp;
}

void quickSort(double *arr, int left, int right) {
	if (left < right) {
		int Lptr;
		int Rptr;
		int partition;
		Lptr = left;
		Rptr = right;
		medianOf3(arr, Lptr, Rptr);
		double pivot = arr[right];
		while (Lptr < Rptr) {
			while (Lptr < Rptr && arr[Lptr] < pivot) {
				++Lptr;
			}
			if (Lptr < Rptr) {
				arr[Rptr] = arr[Lptr];
			}
			while (Lptr < Rptr && arr[Rptr] >= pivot) {
				--Rptr;
			}
			if (Lptr < Rptr) {
				arr[Lptr] = arr[Rptr];
			}
		}
		arr[Rptr] = pivot;
		quickSort(arr, left, Rptr - 1);
		quickSort(arr, Lptr + 1, right);
	}
}

/*
 * INSERTIONSORT
 */
void insertSort(double *arr, int arrlength) {
	int i;
	int j;
	double temp;
	for (i = 1; i < arrlength; ++i) {
		j = i;
		while (j > 0 && arr[j-1] > arr[j]) {
			temp = arr[j];
			arr[j] = arr[j-1];
			arr[j-1] = temp;
			--j;
		}
	}
}

/*
 * COCKTAILSORT
 */
void cocktailSort(double *arr, int len)
{
	int i;
	double temp = 0;
	while (!temp) {
		for (i = 1, temp = 1; i < len; i++) {
			if (arr[i] < arr[i - 1]) {
				temp = arr[i];
				arr[i] = arr[i - 1];
				arr[i - 1] = temp;
				temp = 0;
			}
		};
		if (temp) {
			break;
		}
		for (i = len - 1, temp = 1; i; i--) {
			if (arr[i] < arr[i - 1]) {
				temp = arr[i];
				arr[i] = arr[i - 1];
				arr[i - 1] = temp;
				temp = 0;
			}
		}
	}
}

/*
 * MAIN
 */
int main (int argc, const char* argv[]) {
	FILE *in;
	int i;
	double temp;
	double start;
	double finish;
	double time;
	
	in = fopen(argv[1], "r");
	fscanf(in, "%d", &size);
	printf("size %d\n", size);
	insertArray = (double*)malloc(size*sizeof(double));
	cocktailArray = (double*)malloc(size*sizeof(double));
	quickArray = (double*)malloc(size*sizeof(double));
	
	for (i = 0; i < size; ++i) {
		fscanf(in, "%lg", &temp);
		insertArray[i] = temp;
		cocktailArray[i] = temp;
		quickArray[i] = temp;
	}
	fclose(in);
	
	printf("Start Quicksort...\n");
	start = (double)clock();
	quickSort(quickArray, 0, size-1);
	finish = (double)clock();
	time = (double)((finish - start) / CLOCKS_PER_SEC);
	printf("Quicksort took %f seconds.\n", time);
	
	printf("Start Cocktailsort...\n");
	start = (double)clock();
	cocktailSort(cocktailArray, size);
	finish = (double)clock();
	time = (double)((finish - start) / CLOCKS_PER_SEC);
	printf("Cocktailsort took %f seconds.\n", time);
	
	printf("Start Insertsort...\n");
	start = (double)clock();
	insertSort(insertArray, size);
	finish = (double)clock();
	time = (double)((finish - start) / CLOCKS_PER_SEC);
	printf("Insertsort took %f seconds.\n", time);
	
	free(insertArray);
	free(cocktailArray);
	free(quickArray);
	return 0;
}
