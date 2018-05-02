#!/usr/bin/python3
# This program tries to solve the Salesman Problem with an evolutionary programming approach

import random, numpy, itertools, sys, time
from math import sin, pi, sqrt
from deap import creator, base, tools, algorithms

filename = sys.argv[1]

def distance(t1, t2):
  return sqrt( (t2[1] - t1[1])**2 + (t2[2] - t1[2])**2 )

def coordenadas(filename):
    with open("../datosTSP/" + filename + ".tsp", 'r') as f:

        cities = []
        size = int(f.readline().split(" ")[1])
        for city in range(size):
            data = list(map(float, f.readline().lstrip().split(" ")))
            cities.append((data[0]-1, data[1], data[2]))
            del data

        return cities

# Define vector of cities (index, coordinate_x, coordinate_y)
mapear = coordenadas(filename)

#Matrix of distances
Costs = [[distance(x, y) for y in mapear] for x in mapear]
NUM_CITIES = len(Costs)

# Printer for the populations
def printPop(population):
    for elem in population:
        print ( elem, " ", evalF(elem) )

# Evaluation function
def evalF(individual):
    result = 0
    for pos, elem in enumerate(individual):
        result += Costs[elem][ individual[ (pos+1) % NUM_CITIES] ]
    return result,

# Show the distances of travelling
#print("\n\tCost of travelling from city i to j:")
#print(Costs)

creator.create("FitnessMin", base.Fitness, weights=(-1.0,))
creator.create("Individual", list, fitness=creator.FitnessMin)

toolbox = base.Toolbox()

toolbox.register("indices", random.sample, range(NUM_CITIES), NUM_CITIES)
toolbox.register("individual", tools.initIterate, creator.Individual, toolbox.indices)
toolbox.register("population", tools.initRepeat, list, toolbox.individual)

toolbox.register("evaluate", evalF)
toolbox.register("mate", tools.cxOrdered)
toolbox.register("mutate", tools.mutShuffleIndexes, indpb=0.05)
toolbox.register("select", tools.selTournament, tournsize=3)

CXPB, MUTPB, NGEN = 0.5, 0.2, 1000
population = toolbox.population(n=50)

#print("\n\tBest 20 of the initial population:")
#printPop(tools.selBest(population, k=20))

for _ in itertools.repeat(None, NGEN):
    offspring = algorithms.varAnd(population, toolbox, CXPB, MUTPB)
    fits = toolbox.map(toolbox.evaluate, offspring)
    for fit, ind in zip(fits, offspring):
        ind.fitness.values = fit
    population = toolbox.select(offspring, k=len(population))

#print("\n\tBest 5 of the final population:")
#printPop(tools.selBest(population, k=5))

#output
def outofhere(just_ids):
    output = ""
    just_ids = just_ids[0]
    for idc in just_ids:
      city = next(c for c in mapear if c[0] == idc)
      output += "{0} {1} {2}\n".format(*city)

    with open(filename+".out", 'w') as f:
        f.write(output)

t1 = time.time()
outofhere(tools.selBest(population, k=1))
t2 = time.time()

print(t2-t1)
