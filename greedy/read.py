from math import sqrt

filename = "ulysses16"

def distance(t1, t2):
  return sqrt( (t2[1] - t1[1])**2 + (t2[2] - t1[2])**2 )

def coordenadas(filename):
    with open("datosTSP/" + filename + ".tsp", 'r') as f:

        cities = []
        size = int(f.readline().split(" ")[1])
        for city in range(size):
            data = list(map(float, f.readline().lstrip().split(" ")))
            cities.append((data[0], data[1], data[2]))
            del data
            
        return cities


mapear = coordenadas(filename)

matrix = [[distance(x, y) for y in mapear] for x in mapear]
print(matrix)


#Supongamos que tenemos el vector de la solución

s = [(1, 23.42, 23.12), (2, 12,12)]

def outofhere(solution):
    output = ""

    for city in solution:
        output += "{0} {1} {2}\n".format(*city)

    with open(filename+".out", 'w') as f:
        f.write(output)


outofhere(s)
