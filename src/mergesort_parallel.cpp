#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <iostream>
#include <random>
#include <algorithm>
#include "mpi.h"

using namespace std;

const int LOWER = -100;
const int UPPER = 100;
const int DEF_SIZE = 100;

void merge(int *, int *, int, int, int);
void mergeSort(int *, int *, int, int);

int main(int argc, char** argv) {
	auto start = std::chrono::system_clock::now();
	int size = 0;
	if(argc <= 1)
		size = DEF_SIZE;
	else 
		size = atoi(argv[1]);
	int rank, worldSize;
	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &worldSize);
	int* unsorted = new int[size];
	int* sorted = NULL;
	if(rank == 0){
		random_device randomDevice;
		mt19937 mt(randomDevice());
		uniform_int_distribution<int> dist(LOWER, UPPER);
		for(int i = size; i--; )
			unsorted[i] = dist(mt);
	}
	int chunk = size / worldSize;
	int* subArray = new int[chunk];	
	MPI_Scatter(unsorted, chunk, MPI_INT, subArray, chunk, MPI_INT, 0, MPI_COMM_WORLD);
	int* tempArray = new int[chunk];
	mergeSort(subArray, tempArray, 0, (chunk - 1));		// Llamadas en cada proceso
	if(rank == 0) 
		sorted = new int[size];
	
	MPI_Gather(subArray, chunk, MPI_INT, sorted, chunk, MPI_INT, 0, MPI_COMM_WORLD);
	// Comprobamos todo el array en conjunto
	if(rank == 0) {
		int* copyArray = new int[size];
		mergeSort(sorted, copyArray, 0, (size - 1));
		free(sorted);
		free(copyArray);	
	}
	free(unsorted);
	free(subArray);
	free(tempArray);
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> diff = end - start;		
	cout << diff.count() << endl;
	return 0;
}

void merge(int *a, int *b, int l, int m, int r) {
	int h, i, j, k;
	h = l;
	i = l;
	j = m + 1;
	while((h <= m) && (j <= r)) {
		if(a[h] <= a[j]) {
			b[i] = a[h];
			h++;
		}	
		else {
			b[i] = a[j];
			j++;
			}
		i++;
	}	
	if(m < h) {
		for(k = j; k <= r; k++) {	
			b[i] = a[k];
			i++;
			}
		}
	else {
		for(k = h; k <= m; k++) {	
			b[i] = a[k];
			i++;
		}
	}	
	for(k = l; k <= r; k++) {	
		a[k] = b[k];
		}
	}

void mergeSort(int *a, int *b, int l, int r) {
	int m;
	if(l < r) {	
		m = (l + r)/2;	
		mergeSort(a, b, l, m);
		mergeSort(a, b, (m + 1), r);
		merge(a, b, l, m, r);	
	}	
}