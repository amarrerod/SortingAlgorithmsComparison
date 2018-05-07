#!/bin/python
import os, sys, re


algorithm = "merge"
reps = 10
result_dir = "../results/merge/sequential/"
index_array = []
times_array = [[]]

for filename in os.listdir(result_dir):
    if algorithm in filename:
        fullname = result_dir + filename
        with open(fullname, "r") as f:
            print("File: " + fullname) 
            line = f.readline()
            while True:
                index = int(line)
                if index not in index_array:
                    index_array.append(index)
                    times_array.append([])
                i = index_array.index(index)
                time = f.readline()
                time = float(time)
                times_array[i].append(time)
                if index == 10000000:
                    break
                else:
                    line = f.readline()

filename = "../results/merge/results_sequential.rs"
with open(filename, "a") as f:
    f.write("# " + algorithm)
    for size in index_array:
        i = index_array.index(size)
        print("Size: " + str(size))
        f.write("\n" + str(size))
        for item in times_array[i]:
            f.write("\n" + str(item))