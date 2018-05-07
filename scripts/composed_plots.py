#!/bin/python
import sys
import statistics 
import matplotlib.pyplot as plt

args = 3
reps = 10
basedir = "../results/merge/"
index_array = []
values_1 = []
values_2 = []
values_3 = []


limit = 65536000

def usage():
    print("$ python composed_plots.py <path_to_data_file> <path_to_data_file>\n")

def read_data(path, alg):
    filename = basedir + path    
    with open(filename, "r") as file:
        line = file.readline() # escapamos comentario
        while line:
            index = file.readline()
            index = int(index)
            if alg == 0:
                index_array.append(index)
            result = float(file.readline())
            if alg == 0:
                values_1.append(result)
            else:
                if alg == 1:
                    values_2.append(result)
                else:
                    values_3.append(result)
            if index == limit:
                break

def generate_plot():
    x_data = [i for i in range(0, len(index_array))]
    plt.style.use('fivethirtyeight')
    plt.xticks(x_data, index_array)
    plt.plot(x_data, values_1, color='blue', linewidth=1.2, alpha=0.4, label='Sequential Merge Sort')
    plt.plot(x_data, values_2, color='red', linewidth=1.2, alpha=0.5, label='Parallel Merge Sort')
    plt.plot(x_data, values_3, color='green', linewidth=1.2, alpha=0.7, label='Cuda Sort')
    plt.ylabel("performance time (s)")
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
        read_data(argv[2], 2)
        print(values_1)
        print(values_2)
        print(values_3)
        generate_plot()

if __name__ == '__main__':
    main(sys.argv[1:])