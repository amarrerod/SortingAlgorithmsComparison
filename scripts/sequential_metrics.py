#!/bin/python
import sys
import statistics 

args = 2
reps = 10
basedir = "../results/"
instructions = "#size, mean, median, standard deviation\n"
index_array = []
values_array = []
limit = 10000000

def usage():
    print("$ python sequential_metrics.py <path_to_data_file> <path_to_result_file>\n")

def read_data(path):
    filename = basedir + path    
    with open(filename, "r") as file:
        line = file.readline() # escapamos comentario
        while line:
            index = file.readline()
            index = int(index)
            i = 0
            index_array.append(index)
            values = []
            while i < reps:
                values.append(float(file.readline()))
                i += 1
            values_array.append(values)
            if index == limit:
                break

# Calcula las metricas y las escribe en un fichero
def compute_metrics(path):
    result_file = basedir + path
    with open(result_file, "a") as file:
        file.write(instructions)
        for idx, array in enumerate(values_array):
            avg = statistics.mean(array)
            med = statistics.median(array)
            dev = statistics.pstdev(array)
            size = index_array[idx]
            string = str(size) + ", " + str(avg) + ", " + str(med) + ", " + str(dev) + "\n"
            file.write(string)

def main(argv):
    if(len(argv)!= args):
        print("Error al iniciar el script\n")
        usage()
    else:
        read_data(argv[0])
        compute_metrics(argv[1])

if __name__ == '__main__':
    main(sys.argv[1:])