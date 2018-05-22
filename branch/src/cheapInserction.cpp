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
#include <string.h>

#define prod

using namespace std;

/*

  Ejemplo de uso:
  Con prod definido 

  ./cheap mapa.tour nombre_del_archivo_de_salida

  Con dev definido
  
  ./cheap mapa.tour mapa.opt.tour nombre_del_archivo_de_salida
 */


void printMatrix(vector<vector<double> > matrix){
  for(int i=0; i < matrix.size(); i++){
    for(int j=0; j < matrix[i].size(); j++){
      printf("%.4f ", matrix[i][j]);
    }
    cout << endl;
  }
}

template <typename T>
void printVector(vector<T> v){

  cout << "[";
  for(int i =0; i < v.size()-1; i++){
    cout << v[i] << ",";
  }

  cout << v[v.size()-1];

  cout << "]";
}


double distance(pair<double, double> c1, pair<double, double> c2){
  return hypot(c2.first - c1.first, c2.second - c1.second);
}

int closest_element(int pos, vector<double> &v){
  int shortest = 0;
  int value = v[0];

  if (pos == 0){
    shortest = 1;
    value = v[1];
  }

  for(int i=0; i < v.size(); i++){
    if (v[i] < value && i != pos){
      value = v[i];
      shortest = i;
    }
  }

  return shortest;
}

double compute_addition(int p1, int p2, int p3, vector<vector<double> >&matrix){
  return matrix[p3][p1] + matrix[p2][p3] - matrix[p1][p2];
}

void add_closet_to_path(vector<int> &path, vector<int> &candidatos, int N, vector<vector<double> >& matrix){
  double best_dist = numeric_limits<double>::max();
  double best_dist_global = numeric_limits<double>::max();

  double dist;
  int best_city_global;

  int best_pos_global;
  int best_pos;
  int city;
  //For every city
  for(int i=0; i < candidatos.size(); i++){
    city = candidatos[i];

    //If not in the path compute the best position for the city
    for(int j=0; j < path.size()-1; ++j){
      dist = compute_addition(path[j], path[j+1], city, matrix);

      if (dist < best_dist){
        best_dist = dist;
        best_pos = j;
      }
    }

    if (best_dist < best_dist_global){
      best_pos_global = best_pos;
      best_city_global = i;
      best_dist_global = best_dist;
    }
  }
  path.insert(path.begin()+best_pos_global+1,candidatos[best_city_global]);
  candidatos.erase(candidatos.begin() + best_city_global);
}

double compute_length(vector<int> path, vector<vector<double> > &cities){
  double result = 0;
  for(int i = 0; i < path.size()-1; i++){
    result += cities[path[i]][path[i+1]];
  }
  result += cities[path[0]][path[path.size()-1]];
  return result;
}

int main(int argc, char **argv){

  int N; //Total number of cities
  double x, y; //Variables for data imput
  int n; //Positional argument in input data
  int next_node;
  string filename; //File that contains the input data;
  string output = "salida/cheap_";
  string trash;
  vector<int> result; //Vector of integers representing the order of cities
  int initial;
  double dist;

  std::vector<std::string> args;
  std::copy(argv + 1, argv + argc, std::back_inserter(args));

  output += args[1] + ".tour";

  if(argc > 3){
    cerr << "Error in the number of arguments" << endl;
    return 1;
  }

  //Open the file
  filename = argv[1];
  ifstream data(filename);
  data >> trash;
  data >> N; //First line is always the cardinal of cities

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
    }
  }
  //printMatrix(cities);

  //Start with a random node
  srand (time(NULL));
  initial = rand()%(N);
  initial = 0;
  result.push_back(initial);
  result.push_back(closest_element(initial, cities[initial]));
  std::vector<int> candidatos;

  for(int i = 0; i < N; i++){
    if(i!=initial && i!=result[1])
      candidatos.push_back(i);
  }

  clock_t tStart = clock();
  while(!candidatos.empty()){
    add_closet_to_path(result,candidatos, N, cities);
  }
  clock_t finish = clock();

  #ifdef dev
  cout << "Ciudades: ";
  printVector(result);
  cout << " Total: " << result.size() << endl;
  cout << "Total distance: " << compute_length(result, cities) << endl;
  #endif

  #ifdef prod
  cout << compute_length(result, cities) << "\t" << ((double)finish - tStart)/CLOCKS_PER_SEC << endl;
  #endif

  ofstream out(output);
  int city;
  for(int i =0; i < result.size(); i++){
    city = result[i];
    out << city << " " << coordinates[city].first << " " << coordinates[city].second << endl;
  }


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
  cout << "Solución ofrecida: ";
  printVector(ciudades);
  cout << endl;
  #endif

  return 0;
}
