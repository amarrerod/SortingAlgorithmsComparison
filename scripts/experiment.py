#!/bin/python

sizes = [500, 1000, 2000, 5000, 10000, 15000, 30000, 50000, 75000, 100000, 250000, 350000, 500000, 750000, 1000000, 1500000, 2000000, 5000000, 7500000, 10000000]
algorithms = ["merge_sequential", "merge_parallel", "quicksort"]
reps = 10  # Repeat each configuration 10 times
np = 4

for alg in algorithms:
    for i in sizes:
        filename = alg + ".sh"
        j = 0
        while j < reps:
            with open(filename, "a") as file:
                experiment = ""
                if "parallel" in alg:
                    experiment = "mpirun -np 4 "
                experiment += "../src/" + alg + " " + str(i) + " >> ../results/" + alg + "_" + str(j) + ".rs\n"
                file.write(experiment)
            j += 1