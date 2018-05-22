import sys
from random import uniform



def gencoordinates(n):
    m = 0
    factor=n*1.2
    return uniform(m, factor*n), uniform(m, factor*n)

def generateMap(size):

    output = ""
    output += "DIMENSION: {}\n".format(size)
    for i in range(1, size+1):
        line = "{0} {1:.3f} {2:.3f}\n".format(i, *gencoordinates(size))
        output += line

    return output
        
if __name__ == "__main__":

    if len(sys.argv) != 3:
        print("Error in the number of arguments")
        print("python generarMapa.py N nombre")
    else:
        size = int(sys.argv[1])
        name = sys.argv[2]
        
        salida = generateMap(size)
        with open(name + '.tsp', 'w') as f:
            f.write(salida)
