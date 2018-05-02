#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <utility>
#include <cmath>
#include <algorithm>
#include <limits>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#define prod

using namespace std;

void printMatrix(vector<vector<double> > &matrix){
  for(int i=0; i < matrix.size(); i++){
    for(int j=0; j < matrix[i].size(); j++){
      printf("%.4f ", matrix[i][j]);
    }
    cout << endl;
  }
}

template <typename T>
void printVector(vector<T> &v){

  cout << "vector = [";
  for(int i =0; i < v.size()-1; i++){
    cout << v[i] << ",";
  }

  cout << v[v.size()-1];

  cout << "]" << endl;
}


double distance(pair<double, double> c1, pair<double, double> c2){
  return hypot(c2.first - c1.first, c2.second - c1.second);
}

double compute_length(vector<int> &path, const vector<vector<double> > &cities){
  double result = 0;
  for(int i = 0; i < path.size()-1; i++){
    result += cities[path[i]][path[i+1]];
  }
  result += cities[0][path[path.size()-1]];
  return result;
}

struct gen{
  vector<int> v;
  double f_eval;
};

// Create the initial population randomly
// The population has NOT been evaluated
void InitializePopulation(vector<gen*> &population, int pob_size, int n_cities) {
    population.clear();

    vector<int> permutation;
    for (int i=0; i<n_cities; i++)
      permutation.push_back(i);

    for (int i=0; i<pob_size; i++) {
      gen *aux_gen = new gen;;
      aux_gen->v = permutation;
      random_shuffle(aux_gen->v.begin(), aux_gen->v.end());
      population.push_back(aux_gen);
    }
}

// This function returns the best gen in v (selected by minimizing f_eval)
// Prec.: v.size() > 0
gen* SelectBest(const vector<gen*> &v) {
  int best_i = 0;
  double best_f = v[0]->f_eval;
  for (int i=1; i<v.size(); i++) {
    if (v[i]->f_eval < best_f) {
      best_i = i;
      best_f = v[i]->f_eval;
    }
  }
  return v[best_i];
}

// This function applies tournament selection to "population"
gen* TournamentSelection(const vector<gen*> &population) {
  vector<gen*> tour;
  int size = population.size(), tournament_size = 3;

  for (int j=0; j<tournament_size; j++) {
    int r = rand() % size;
    tour.push_back( population[r] );
  }
  return SelectBest(tour);
}

// Generates two children from the parents provided using Order Cross
// Warning: the childrens f_eval has not been updated
// Prec.: Children already initialized
void OrderCrossover (gen *p1, gen *p2, gen *child1, gen *child2) {
  int size = p1->v.size();
  int rand_top = rand() % (size - 2) + 2;
  int rand_bottom = rand() % (rand_top - 1);

  vector<bool> used1 (size, false), used2 (size, false);

  for (int i=rand_bottom; i<=rand_top; i++) {
    child1->v.push_back(p1->v[i]);
    used1[p1->v[i]] = true;
    child2->v.push_back(p2->v[i]);
    used2[p2->v[i]] = true;
  }

  for (int i=(rand_top+1) % size ; i != rand_top ; i = (i+1)%size) {
    if (!used1[p2->v[i]]) {
      used1[p2->v[i]] = true;
      child1->v.push_back(p2->v[i]);
    }
    if (!used2[p1->v[i]]) {
      used2[p1->v[i]] = true;
      child2->v.push_back(p1->v[i]);
    }
  }
  if (!used1[p2->v[rand_top]]) {
    child1->v.push_back(p2->v[rand_top]);
  }
  if (!used2[p1->v[rand_top]]) {
    child2->v.push_back(p1->v[rand_top]);
  }
}

void ApplySelectionAndCrossover(const vector<gen*> &parents, vector<gen*> &children) {
  children.clear();
  int size = parents.size() / 2;
  for (int i=0; i<size; i++) {
    gen *p1 = TournamentSelection(parents);
    gen *p2 = TournamentSelection(parents);
    gen *child1 = new gen, *child2 = new gen;

    OrderCrossover(p1, p2, child1, child2);
    children.push_back(child1);
    children.push_back(child2);
  }
}

void InsertionMutation(gen *g, int rand_top) {
  int size = g->v.size();
  //int rand_top = rand() % (size - 2) + 2;
  int rand_bottom = rand() % (rand_top - 1);

  int holder = g->v[rand_top];
  for (int i=rand_top-1 ; i >= rand_bottom; i--) {
    g->v[i+1] = g->v[i];
  }

  g->v[rand_bottom] = holder;
}

// Returns a random number within [0,1)
double dRand() {
  return (double)rand() / RAND_MAX;
}

// Apply a mutation to each member of the population with a probability "prob"
void ApplyMutation(vector<gen*> &population, double prob) {
  double r;
  for (int i=0; i<population.size(); i++) {
    for (int j=2; j<population[i]->v.size(); j++) {
      r = dRand();
      if (r < prob) {
        InsertionMutation(population[i], j);
      }
    }
  }
}

// Evaluates the population and saves the best solution found
void EvaluatePopulation (vector<gen*> &population, gen &best_gen,
      const vector<vector<double> > &cities ) {
  for (int i=0; i<population.size(); i++) {
    population[i]->f_eval = compute_length(population[i]->v, cities);
    if (population[i]->f_eval < best_gen.f_eval) {
      best_gen = *population[i];
    }
  }
}

// Replace the elements in population with the elements from the new_generation
// Prec.: population.size() == new_generation.size()
void ReplaceGeneration(vector<gen*> &population, vector<gen*> &new_generation) {
  for (int i=0; i<population.size(); i++) {
    delete population[i];
    population[i] = new_generation[i];
  }
}

void PrintPop(vector<gen*> &pop) {
  for (int i=0; i<pop.size(); i++) {
    cout << "Element " << i << endl;
    printVector(pop[i]->v);
  }
}

void genetic(vector<int> &solution, const vector<vector<double> > &cities){
  int pob_size = 500, n_generations = 500;
  int n_cities = cities.size();
  double mutate_propability = 0.05;

  vector<gen*> population;
  vector<gen*> new_generation;
  gen best_gen_ever;

  srand(time(NULL));

  // Initialize the population and evaluate it
  InitializePopulation(population, pob_size, n_cities);
  best_gen_ever = *population[0];
  EvaluatePopulation(population, best_gen_ever, cities);

  //PrintPop(population);

  for (int i=0; i<n_generations; i++) {
    // Obtain the next generation and apply crossover from the elements of population
    ApplySelectionAndCrossover(population, new_generation);

    // Apply mutation to the new population with a probability prob
    ApplyMutation(new_generation, mutate_propability);

    // Evaluate the new population and save the best solution found
    EvaluatePopulation(new_generation, best_gen_ever, cities);

    // Replace the old population with the new one
    ReplaceGeneration(population, new_generation);
  }

  // Return the solution
  solution = best_gen_ever.v;
}

int main(int argc, char **argv){
  int N; //Total number of cities
  double x, y; //Variables for data imput
  int n; //Positional argument in input data
  int next_node;
  string filename; //File that contains the input data;
  string output = "salida/genetic_";
  string trash;
  vector<int> ini, result; //Vector of integers representing the order of cities
  int initial;

  if(argc != 3){
    cerr << "Error in the number of arguments" << endl;
    return 1;
  }
  
  std::vector<std::string> args;
  std::copy(argv + 1, argv + argc, std::back_inserter(args));

  output += args[1] + ".tour";
  
  cout << output <<endl;

  //Open the file
  filename = argv[1];
  ifstream data(filename);
  data >> trash;
  data >> N; //First line is always the cardinal of cities

  int mini, minj;
  double dist, best=numeric_limits<int>::max();

  //Create a vector of 3-uplas
  vector<pair<double, double> > coordinates;

  //Create an square matrix
  vector<vector<double> > cities(N, vector<double>(N,0));

  //Store all the input data
  for(int i=0; i < N; i++){
    data >> n >> x >> y;
    coordinates.push_back({x,y});
  }

  for(int i = 0; i < N; i++){
    for(int j=0; j < i; j++){
      dist = distance(coordinates[i], coordinates[j]);
      cities[i][j] = dist;
      cities[j][i] = cities[i][j];

      if(dist < best){
      	mini = i;
      	minj = j;
      	best = dist;
      }
    }

    best=numeric_limits<int>::max();
  }
  cout << N << endl;
  //printMatrix(cities);

  clock_t tStart = clock();
  genetic(result, cities);
  clock_t finish = clock();

  //printVector(result);
  #ifdef dev
  cout << "Ciudades: ";
  printVector(result);
  cout << " Total: " << result.size() << endl;
  cout << "Total distance: " << compute_length(result, cities) << endl;
  #endif
  
  ofstream out(output);
  int city;
  for(int i =0; i < result.size(); i++){
    city = result[i];
    out << city << " " << coordinates[city].first << " " << coordinates[city].second << endl;
  }
  
  #ifdef prod
  cout << compute_length(result, cities) << "\t" << ((double)finish - tStart)/CLOCKS_PER_SEC << endl;
  #endif

  //Obtener el grafico de la solución en el  dataset propuesto
  #ifdef dev
  ifstream archivo(argv[2]);
  vector<int> ciudades;
  int k;
  archivo >> trash;
  archivo >> k;
  for(int i =0; i < N; i++){
    archivo >> k;
    ciudades.push_back(k-1);
  }

  ofstream salida("salida_suya.tour");
  for(int i =0; i < ciudades.size(); i++){
    city = ciudades[i];
    salida << city << " " << coordinates[city].first << " " << coordinates[city].second << endl;
  }

  cout << "La longitud de la solución ofrecida es: " << compute_length(ciudades, cities) << endl;
  #endif

  return 0;
}
