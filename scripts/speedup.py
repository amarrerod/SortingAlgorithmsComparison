#!/bin/python

size = 1000000000
algorithms = ["merge_parallel"]
np = [2, 4, 6, 8, 10, 12, 14, 16, 10, 20]

for alg in algorithms:
    for i in np:
        filename = alg + "_speedup.sh"
        with open(filename, "a") as file:
            experiment = "mpirun -np " + str(i) + " "
            experiment += "../src/" + alg + " " + str(size) + " >> ../results/speedup/" + alg + "_" + str(i) + ".rs\n"
            file.write(experiment)