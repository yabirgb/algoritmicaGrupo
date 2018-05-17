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

using namespace std;

int MAX = 100;
vector< vector< int> > afinidades;
vector< vector< int> > aversiones;

void GenerarAfinidadesAversiones(int n_comensales, int seed) {
  srand(12345678 * seed);
  vector< vector<int> > m (n_comensales, vector<int>(n_comensales, 0));
  aversiones = m;

  for (int i=0; i<n_comensales; i++) {
    for (int j=0; j<n_comensales; j++) {
      m[i][j] = rand() % MAX+1;
    }
  }

  afinidades = m;

  for (int i=0; i<m.size(); i++) {
    for (int j=0; j<m.size(); j++) {
      m[i][j] = afinidades[i][j] + afinidades[j][i];
      aversiones[i][j] = 2*MAX - m[i][j];
    }
  }

  afinidades = m;
}

void printMatrix(vector<vector<int> > &matrix){
  for(int i=0; i < matrix.size(); i++){
    cout << "[ ";
    for(int j=0; j < matrix[i].size(); j++){
      cout << matrix[i][j] << " ";
    }
    cout << "]" << endl;
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

double evaluate(vector<int> &v, const vector<vector<int> > &m){
  double result = 0;
  for(int i = 0; i < v.size()-1; i++){
    result += m[v[i]][v[i+1]];
  }
  result += m[v[0]][v[v.size()-1]];
  return result;
}

struct gen{
  vector<int> v;
  double f_eval;
};

// Create the initial population randomly
// The population has NOT been evaluated
void InitializePopulation(vector<gen*> &population, int pob_size, int n_comen) {
    population.clear();

    vector<int> permutation;
    for (int i=0; i<n_comen; i++)
      permutation.push_back(i);

    for (int i=0; i<pob_size; i++) {
      gen *aux_gen = new gen;
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
      const vector<vector<int> > &aversiones ) {
  for (int i=0; i<population.size(); i++) {
    population[i]->f_eval = evaluate(population[i]->v, aversiones);
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

double AvFitness (vector<gen*> &population,
      const vector<vector<int> > &aversiones ) {
  double total_f = 0;
  for (int i=0; i<population.size(); i++) {
    total_f += evaluate(population[i]->v, aversiones);
  }
  return total_f / population.size();
}

double genetic(vector<int> &solution, const vector<vector<int> > &aversiones){
  int pob_size = 500, n_generations = 200;
  int n_comen = aversiones.size();
  double mutate_propability = 0.05;
  double initial_pop_av_fit;

  vector<gen*> population;
  vector<gen*> new_generation;
  gen best_gen_ever;

  srand(time(NULL));

  // Initialize the population and evaluate it
  InitializePopulation(population, pob_size, n_comen);
  best_gen_ever.f_eval = numeric_limits<int>::max();
  EvaluatePopulation(population, best_gen_ever, aversiones);

  //PrintPop(population);

  for (int i=0; i<n_generations; i++) {
    // Obtain the next generation and apply crossover from the elements of population
    ApplySelectionAndCrossover(population, new_generation);

    // Apply mutation to the new population with a probability prob
    ApplyMutation(new_generation, mutate_propability);

    // Evaluate the new population and save the best solution found
    EvaluatePopulation(new_generation, best_gen_ever, aversiones);

    // Replace the old population with the new one
    ReplaceGeneration(population, new_generation);

    //cout << "Generation: " << i << ". Fitness: " << best_gen_ever.f_eval << endl;
    //printVector(best_gen_ever.v);
  }

  // Return the solution
  solution = best_gen_ever.v;

  return best_gen_ever;
}

int main(int argc, char **argv){
  if(argc != 2){
    cerr << "Ejecución: ./" << argv[0] << " <max_n_comensales>" << endl;
    return 1;
  }

  int max_n_comensales = atoi(argv[1]);

  GenerarAfinidadesAversiones(n_comen, j);
  // Al genetico le pasamos el vector para almacenar la solucion y la matriz sobre la que operamos.
  // Devuelve el fitness del elemento
  double resultado_vota_increible = genetic(result, aversiones);



    // TODO LO QUE HAY AQUI DEBAJO ES BORRABLE, NO SE QUE USO QUEREIS HACER DE ELLO
  int n_repetitions = 10;
  ofstream output_times("datos/genetic_times.dat");
  ofstream output_sol("datos/genetic_sol.dat");
  ofstream output_initial_sol("datos/genetic_initial_sol.dat");
  vector<int> result;
  double total_time, total_aversion, total_initial_fit;

  for (int n_comen=3; n_comen<=max_n_comensales; n_comen++) {
    total_time = 0;
    total_aversion = 0;
    total_initial_fit = 0;

    for (int j=0; j<n_repetitions; j++) {

      GenerarAfinidadesAversiones(n_comen, j);
      //printMatrix(aversiones);

      clock_t tStart = clock();
      total_initial_fit += genetic(result, aversiones);
      clock_t finish = clock();

      total_time += ((double)finish - tStart)/CLOCKS_PER_SEC;
      total_aversion += evaluate(result, aversiones);
    }

    total_time /= n_repetitions;
    total_aversion /= n_repetitions;
    total_initial_fit /= n_repetitions;
    output_times << n_comen << "\t" << total_time << endl;
    output_sol << n_comen << "\t" << total_aversion << endl;
    output_initial_sol << n_comen << "\t" << total_initial_fit << endl;

    cout << "Mejor solución: ";
    printVector(result);
    cout << "Con aversión: " << evaluate(result, aversiones) << endl;
  }
}
