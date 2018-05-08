MPI=mpic++
GCC=g++
CUDA=nvcc
CFLAGS= -arch=compute_35
FLAGS=-std=c++11

all: merge_parallel merge_sequential merge_cuda

merge_sequential: mergesort_sequential.cpp
	$(GCC) $(FLAGS) -o $@ $^

merge_parallel: mergesort_parallel.cpp
	$(MPI) $(FLAGS) -o $@ $^

merge_cuda: merge_cuda.cu
	$(CUDA) $(FLAGS) -O3 -arch=sm_21 -lboost_chrono -lboost_system -o $@ $^

clean:
	rm merge_sequential
	rm merge_parallel
	rm merge_cuda