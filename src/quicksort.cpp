#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <iostream>
#include <random>
#include <algorithm>

using namespace std;

const int LOWER = -100;
const int UPPER = 100;
const int DEF_SIZE = 100;

void quicksort(int *, int, int);

int main(int argc, char** argv) {
	auto start = std::chrono::system_clock::now();
	int size = 0;
	if(argc <= 1)
		size = DEF_SIZE;
	else 
		size = atoi(argv[1]);
	int* unsorted = new int[size];
	random_device randomDevice;
	mt19937 mt(randomDevice());
	uniform_int_distribution<int> dist(LOWER, UPPER);
	for(int i = size; i--; ){
		unsorted[i] = dist(mt);
	}
	quicksort(unsorted, 0, (size - 1));
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> diff = end - start;			
	cout << size << endl << diff.count() << endl;
	delete unsorted;
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