#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <boost/chrono.hpp>
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/sort.h>

void rnd_fill(thrust::host_vector<double> &V, const double lower, const double upper, const unsigned int seed) {
    srand(time(NULL));
    size_t elem = V.size();
    for( size_t i = 0; i < elem; ++i){
        V[i] = (double) rand() / (double) RAND_MAX;
    }
}

int main() {
    thrust::host_vector<double> V;
    thrust::device_vector<double> d_V;
    //use the system time to create a random seed
    unsigned int seed = (unsigned int) time(NULL);
    size_t mem = 100000000;
    for(int i = 500; i <= mem; i *= 2 ) {
        V.resize(i);
        rnd_fill(V, -100.0, 100.0, seed);
        boost::chrono::steady_clock::time_point start_cpu = boost::chrono::steady_clock::now();
        d_V = V; // Transfer data to the GPU
        boost::chrono::steady_clock::time_point end_cpu = boost::chrono::steady_clock::now();
        double dt1 = boost::chrono::duration <double, boost::milli> (end_cpu - start_cpu).count();
	    cudaEvent_t start, stop;
	    cudaEventCreate(&start);
	    cudaEventCreate(&stop);
	    //Start recording
	    cudaEventRecord(start,0);
        thrust::stable_sort(d_V.begin(), d_V.end());
	    //Stop recording
	    cudaEventRecord(stop,0);
	    cudaEventSynchronize(stop);
	    float elapsedTime;
	    cudaEventElapsedTime(&elapsedTime, start, stop);
	    cudaEventDestroy(start);
	    cudaEventDestroy(stop);
        start_cpu = boost::chrono::steady_clock::now();
        V = d_V; // Transfer data to the CPU
        end_cpu = boost::chrono::steady_clock::now();
        double dt2 = boost::chrono::duration <double, boost::milli> (end_cpu - start_cpu).count();
	    std::cout << i << std::endl << ((elapsedTime + dt1 + dt2) * 0.001) << std::endl;
    }
    return 0;
}

