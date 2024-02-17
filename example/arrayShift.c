
#include <stdio.h>
#include <stdlib.h>

void shift(int *arr, int size, int n);

void printArray(int *arr, int size);

int main(void) {
	printf("Enter array size: ");
	int size = 0;
	if (scanf("%d", &size) != 1) {
		fprintf(stderr, "error: failed to read array size\n");
		exit(EXIT_FAILURE);
	} else if (size < 0) {
		fprintf(stderr, "error: invalid array size\n");
		exit(EXIT_FAILURE);
	}

	int *arr = malloc(size * sizeof(int));
	if (arr == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
	}

	if (size > 0) {
		printf("Enter array values: ");
	}
	for (int i = 0; i < size; i++) {
		if (scanf("%d", &arr[i]) != 1) {
			fprintf(stderr, "error: failed to read array value\n");
			exit(EXIT_FAILURE);
		}
	}

	printf("Array: ");
	printArray(arr, size);

	printf("Enter shift: ");
	int n = 0;
	if (scanf("%d", &n) != 1) {
		fprintf(stderr, "error: failed to read shift\n");
		exit(EXIT_FAILURE);
	} else if (n < 0) {
		fprintf(stderr, "error: invalid shift\n");
		exit(EXIT_FAILURE);
	}

	shift(arr, size, n);
	printf("Array after shifting %d time(s): ", n);
	printArray(arr, size);

	free(arr);
	return EXIT_SUCCESS;
}

// !!! DO NOT MODIFY THE CODE ABOVE !!!
////////////////////////////////////////////////////////////////////////
// Your task

void shift(int *arr, int size, int n) {
	// If n is > size, make it not so
	n = n % size;
	//No shifting required
	if(size == 0 || n == 0) return;

	// No loops
	// 	1. Reverse (size - n) elements from head
	// 	2. Reverse remaining elements
	//  3. Reverse all elements
	int tmp;
	// 1.
	// First size - n from head
	for(int head = 0, tail = size - n - 1; head < tail; head++, tail--) {
		// This should be in a reverse function
		tmp = arr[head];
		arr[head] = arr[tail];
		arr[tail] = tmp;
	}

	// 2.
	// Remaining tail elements
	for(int head = size - n, tail = size - 1; head < tail; head++, tail--) {
		tmp = arr[head];
		arr[head] = arr[tail];
		arr[tail] = tmp;
	}

	// 3. 
	// Reverse entire array
	for(int head = 0, tail = size - 1; head < tail; head++, tail--) {
		tmp = arr[head];
		arr[head] = arr[tail];
		arr[tail] = tmp;
	}
}

////////////////////////////////////////////////////////////////////////
// !!! DO NOT MODIFY THE CODE BELOW !!!

void printArray(int *arr, int size) {
	printf("[");
	for (int i = 0; i < size; i++) {
		if (i > 0) {
			printf(", ");
		}
		printf("%d", arr[i]);
	}
	printf("]\n");
}

