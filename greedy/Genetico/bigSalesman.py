#!/usr/bin/python3
# This program tries to solve the Salesman Problem with an evolutionary programming approach

import random, numpy, itertools
from math import sin, pi
from deap import creator, base, tools, algorithms

# Define vector of cities
NUM_CITIES = 100
CITIES = [x for x in range(NUM_CITIES)]

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

# Define the costs of travelling
NCPB = 5
Costs = [[x for x in range(NUM_CITIES)] for _ in range(NUM_CITIES)]
for i in range(NUM_CITIES):
    for j in range(NUM_CITIES):
        #if (random.randint(1,100) <= NCPB):
        #    Costs[i][j] = -1
        #else:
            Costs[i][j] = numpy.random.uniform(10,40,None)

print("\n\tCost of travelling from city i to j:")
print(Costs)

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

print("\n\tBest 20 of the initial population:")
printPop(tools.selBest(population, k=20))

for _ in itertools.repeat(None, NGEN):
    offspring = algorithms.varAnd(population, toolbox, CXPB, MUTPB)
    fits = toolbox.map(toolbox.evaluate, offspring)
    for fit, ind in zip(fits, offspring):
        ind.fitness.values = fit
    population = toolbox.select(offspring, k=len(population))

print("\n\tBest 5 of the final population:")
printPop(tools.selBest(population, k=5))
