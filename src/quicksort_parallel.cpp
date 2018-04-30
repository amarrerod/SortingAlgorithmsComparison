
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

void quicksort(int* array, int begin, int end);
void hyperquicksort(int* array, int chunk, int size);

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
    int middle = 0;
    // Cada proceso comienza con un quicksort secuencial en su lista local
    MPI_Scatter(unsorted, chunk, MPI_INT, subArray, chunk, MPI_INT, 0, MPI_COMM_WORLD);
    quicksort(subArray, 0, chunk - 1);
    MPI_Barrier(MPI_COMM_WORLD);
    // Hyperquicksort
    hyperquicksort(subArray, chunk, size);
    for(int i = 0; i < worldSize; i++){
        if(i != rank){
        // Dividimos el array segun el pivote y lo compartimos
        vector<int> lesser;
        vector<int> greater;
        for(int i = 0; i < size; i++){
            if(array[i] < middle)
                lesser.push_back(array[i]);
            else
                greater.push_back(array[i]);
        }
        int* lesserRaw = &lesser[0];
        int* greaterRaw = &greater[0];
        
        }
    }
    return 0;
}

void hyperquicksort(int* array, int chunk, int size) {
    if(rank == 0){ // El master elige el pivote
        middle = subArray[(0 + chunk) / 2];
        MPI_Bcast(&middle, sizeof(int), MPI_INT, 0, MPI_COMM_WORLD); // Lo envia al resto
    }
    MPI_Barrier(MPI_COMM_WORLD);
    // Dividimos la lista
    vector<int> lesser, greater;
    for(int i = 0; i < chunk; i++){
        if(array[i] < middle)
            lesser.push_back(array[i]);
        else
            greater.push_back(array[i]);
    }
    int* lesserRaw = &lesser[0];
    int* greaterRaw = &greater[0];
    int* localList = new int[chunk];
    int tag = 10;
    
    MPI_Send(greaterRaw, sizeof(greaterRaw), MPI_INT, dest, tag, 
    MPI_COMM_WORLD);
}

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

