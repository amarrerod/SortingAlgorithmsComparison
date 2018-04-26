import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
import numpy as np
import os, sys, re

index_array = []
data_array = []
times = []

def load_data(filename):
    with open(filename) as file:
        line = file.readline()
        while line:
            line = file.readline()
            index = int(line)
            index_array.append(index)
            counter = 0
            values = []
            while counter < index:
                print(str(index) + ": ")
                line = file.readline() # Leemos un nuevo dato
                counter += 1
                print(str(float(line)) + " ")
                values.append(float(line))
            data_array.append(values)
            print("\n")
            if index == 20:
                break

def compute_times():
    for i in range(len(data_array)):
        result = sum(data_array[i])
        result = result / len(data_array[i])
        print("Media de " + str(index_array[i]) + ": " + str(result))
        if i > 1:
            result = result / times[0]
        times.append(result)
        print("Times at {}: {}".format(index_array[i], times[i]))

def create_plot():
    x  = index_array[2:]
    y = times[2:]
    plt.plot(x, y, linewidth=2.0)
    plt.ylabel("speed-up")
    plt.xlabel("number of processors")
    plt.show()


def main(argv):
    if(len(argv)!= 1):
        print("Error al iniciar el script\n")
    else:
        load_data(argv[0])
        compute_times()
        create_plot()

if __name__ == '__main__':
    main(sys.argv[1:])