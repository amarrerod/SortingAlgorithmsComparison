
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <iostream>
#include <random>
#include <algorithm>
#include "mpi.h"
#include <vector>

using namespace std;

const int LOWER = -100;
const int UPPER = 100;
const int DEF_SIZE = 100;

void quicksort(int* array, int begin, int end) {
	int pivot = array[(begin + end) / 2];
	int i = begin, j = end;
	while(i <= j){
		while(array[i] < pivot)
			i++;
		while(array[j] > pivot)
			j--;
		if(i <= j){
			int temp = array[i];
			array[i] = array[j];
			array[j] = temp;
			i++;
			j--;
		}
	}
	if(begin < j)
		quicksort(array, begin, j);
	if(i < end)
		quicksort(array, i, end);
}

void sample(int* subArray, int* sampling, int size, int worldSize) {
    int count = 0;
    int index = 0;
    int i = 0;
    while(count < worldSize){
        sampling[i] = subArray[index];
        i++;
        index = (i * size) / pow(wordlSize, 2);
        count++;
    }
}

void split(int* array, int size, int rank, int pieces, firstP, secondP) {
    vector<vector<int>> partitions(pieces, vector<int>);
    for(int i = 0; i < size; i++){
        if(array[i] < firstP)
           partitions[] 
    }
}

int main(int argc, char** argv){
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
    // Cada proceso comienza con un quicksort secuencial en su lista local
    MPI_Scatter(unsorted, chunk, MPI_INT, subArray, chunk, MPI_INT, 0, MPI_COMM_WORLD);
    quicksort(subArray, 0, chunk - 1);
    int* sampling = new int[worldSize];
    sample(subArray, sampling, size, worldSize);
    int* local = new int[worldSize * worldSize];
    MPI_Gather(sampling, sizeof(sampling), MPI_INT, local, sizeof(sampling), MPI_INT, 0, MPI_COMM_WORLD);
    quicksort(local, 0, (worldSize * worldSize) - 1);
    int firstPivot = 0, secondPivot = 0;
    if(rank == 0){ // Obtenemos los pivotes
        int index = (worldSize * worldSize) / 2;
        firstPivot = local[index];
        secondPivot = local[index + worldSize];
        MPI_Bcast(&firstPivot, sizeof(firstPivot), MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(&secondPivot, sizeof(secondPivot), MPI_INT, 0, 
        MPI_COMM_WORLD);
    }
    // Particionar e intercambiar
    // Dividimos cada subArray en P-1 trozos
    split(subArray, chunk, rank, worldSize, firstPivot, secondPivot);    
    return 0;
}