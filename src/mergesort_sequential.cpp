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

void merge(int *, int *, int, int, int);
void mergeSort(int *, int *, int, int);

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;

int main(int argc, char** argv) {
	int size = 0;
	if(argc <= 1)
		size = DEF_SIZE;
	else 
		size = atoi(argv[1]);
	int* unsorted = new int[size];
	int* sorted = new int[size];
	random_device randomDevice;
	mt19937 mt(randomDevice());
	uniform_int_distribution<int> dist(LOWER, UPPER);
	for(int i = size; i--; ){
		unsorted[i] = dist(mt);
	}
	auto start = Time::now();
	mergeSort(unsorted, sorted, 0, (size - 1));
	auto end = Time::now();
	fsec fs = end - start;	
	cout << size << endl << fs.count() << endl;
	delete unsorted;
	delete sorted;
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