/*
 * @Author: Alejandro Marrero 
 * @Contact: alu0100825008@ull.edu.es 
 * @Date: 2018-05-08 18:56:58 
 * @Last Modified time: 2018-05-08 18:56:58 
 */
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <boost/chrono.hpp>
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/sort.h>

const int LOWER = 0.0;
const int UPPER = 1.0;

void fillVector(thrust::host_vector<double> &V, const double lower, const double upper, const unsigned int seed) {
    srand(time(NULL));
    size_t elem = V.size();
    for( size_t i = 0; i < elem; ++i){
        V[i] = (double) rand() / (double) RAND_MAX;
    }
}

int main() {
    thrust::host_vector<double> hostVector;
    thrust::device_vector<double> deviceVector;
    unsigned int seed = (unsigned int) time(NULL);
    size_t limit = 100000000;
    for(int i = 500; i <= limit; i *= 2 ) {
        hostVector.resize(i);
        fillVector(V, LOWER, UPPER, seed);
        boost::chrono::steady_clock::time_point start_cpu = boost::chrono::steady_clock::now();
        deviceVector = hostVector;
        boost::chrono::steady_clock::time_point end_cpu = boost::chrono::steady_clock::now();
        double durationCPU = boost::chrono::duration <double, boost::milli> (end_cpu - start_cpu).count();
	    cudaEvent_t start, stop;
	    cudaEventCreate(&start);
	    cudaEventCreate(&stop);
	    cudaEventRecord(start,0);
        thrust::stable_sort(d_V.begin(), d_V.end());
	    cudaEventRecord(stop,0);
	    cudaEventSynchronize(stop);
	    float elapsedTime;
	    cudaEventElapsedTime(&elapsedTime, start, stop);
	    cudaEventDestroy(start);
	    cudaEventDestroy(stop);
        start_cpu = boost::chrono::steady_clock::now();
        hostVector = deviceVector;
        end_cpu = boost::chrono::steady_clock::now();
        double durationCPU_2 = boost::chrono::duration <double, boost::milli> (end_cpu - start_cpu).count();
	    std::cout << i << std::endl << ((elapsedTime + durationCPU + durationCPU_2) * 0.001) << std::endl;
    }
    return 0;
}

