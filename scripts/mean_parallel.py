import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
import numpy as np
import os, sys, re

index_array = []
data_array = []
times = []
processors = 4
limit = 65536000

def load_data(filename):
    with open(filename) as file:
        line = file.readline()
        while line:
            line = file.readline()
            tokens = line.split(" ")
            if len(tokens) != 5:
                exit()
            print("Index: {}, data: {}".format(tokens[0], tokens[1:]))
            index = int(tokens[0])
            index_array.append(tokens[0])
            data_array.append(np.array(tokens[1:], dtype=float))
            if index == limit:
                break
    print("Index: {}".format(index_array))
    print("Values: {}".format(data_array))

def compute_times(filename):
    with open(filename, "w") as file:
        for i in range(len(data_array)):
            result = sum(data_array[i])
            result = result / len(data_array[i])
            times.append(result)
            file.write("{}\n{}\n".format(index_array[i], times[i]))
            print("{}\n{}\n".format(index_array[i], times[i]))

def main(argv):
    if(len(argv)!= 2):
        print("Error al iniciar el script\n")
    else:
        load_data(argv[0])
        compute_times(argv[1])

if __name__ == '__main__':
    main(sys.argv[1:])