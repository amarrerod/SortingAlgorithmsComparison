#!/bin/python
import sys
import statistics 
import matplotlib.pyplot as plt

args = 2
reps = 10
basedir = "../results/"
index_array = []
values_1 = []
values_2 = []

mean_algorithm1 = []
mean_algorithm2 = []

limit = 10000000

def usage():
    print("$ python composed_plots.py <path_to_data_file> <path_to_data_file>\n")

def read_data(path, alg):
    filename = basedir + path    
    with open(filename, "r") as file:
        line = file.readline() # escapamos comentario
        while line:
            index = file.readline()
            index = int(index)
            i = 0
            if alg == 0:
                index_array.append(index)
            values = []
            while i < reps:
                values.append(float(file.readline()))
                i += 1
            if alg == 0:
                values_1.append(values)
            else:
                values_2.append(values)
            if index == limit:
                break

# Calcula la media
def compute_metrics(alg):
    if alg == 0:
        array = values_1
    else:
        array = values_2
    for idx, ary in enumerate(array):
        avg = statistics.mean(ary)
        if alg == 0:
            mean_algorithm1.append(avg)
        else:
            mean_algorithm2.append(avg) 

def generate_plot():
    x_data = [i for i in range(0, len(index_array))]
    plt.style.use('fivethirtyeight')
    plt.xticks(x_data, index_array)
    plt.plot(x_data, mean_algorithm1, color='blue', linewidth=1, alpha=0.4, label='MSort')
    plt.plot(x_data, mean_algorithm2, color='red', linewidth=1, alpha=0.7, label='QSort')
    plt.ylabel("performance mean time (s)")
    plt.xlabel("number of items to sort")
    plt.legend(bbox_to_anchor=(0., 1.02, 1., .102), loc=3, ncol=1, mode="expand", borderaxespad=0)
  #  plt.legend([mean_algorithm1, mean_algorithm2], ["Merge Sort", "Quick Sort"])
    plt.show()

def main(argv):
    if(len(argv)!= args):
        print("Error al iniciar el script\n")
        usage()
    else:
        read_data(argv[0], 0)
        read_data(argv[1], 1)
        compute_metrics(0)
        compute_metrics(1)
        print(mean_algorithm1)
        print(mean_algorithm2)
        generate_plot()

if __name__ == '__main__':
    main(sys.argv[1:])