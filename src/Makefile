MPI=mpic++
GCC=g++
FLAGS=-std=c++11

all: merge_parallel merge_sequential quicksort

merge_sequential: mergesort_sequential.cpp
	$(GCC) $(FLAGS) -o $@ $^

merge_parallel: mergesort_parallel.cpp
	$(MPI) $(FLAGS) -o $@ $^

quicksort: quicksort.cpp
	$(GCC) $(FLAGS) -o $@ $^

clean:
	rm merge_sequential
	rm merge_parallel
	rm quicksort
