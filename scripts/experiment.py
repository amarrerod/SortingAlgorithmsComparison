#!/bin/python

initial = 500
limit = 100000000
algorithms = ["merge_sequential", "merge_parallel"]
reps = 1  # Repeat each configuration 10 times
np = 4

for alg in algorithms:
    i = initial
    while i <= limit:
        filename = alg + ".sh"
        j = 0
        while j < reps:
            with open(filename, "a") as file:
                experiment = ""
                if "parallel" in alg:
                    experiment = "mpirun -np 4 "
                experiment += "../src/" + alg + " " + str(i) + " >> ../results/merge/" + alg + "_" + str(j) + ".rs\n"
                file.write(experiment)
            j += 1
        i *= 2