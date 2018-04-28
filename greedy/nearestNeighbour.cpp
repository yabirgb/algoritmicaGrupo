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

int nearest_neighbour(vector<double> &d, vector<int> &c){
  double value = numeric_limits<double>::max();
  int shortest = c[0];
  
  for(int i=0; i < d.size(); i++){
    if (d[i] < value && find(c.begin(), c.end(), i) != c.end()){
      value = d[i];
      shortest = i;
    }
  }

  return find(c.begin(), c.end(), shortest) - c.begin();
}

void greedy(vector<int> &ini, vector<int> &res, vector<vector<double> > &matrix){
  int best_pos = 0;
  int pos = 0;
  int n = matrix.size();
  int initial;
  
  srand (time(NULL));
  initial = rand()%(n);
  
  res.push_back(initial);
  ini.erase(ini.begin() + initial);
  
  for(pos=0; pos<n-1; pos++){
    best_pos = nearest_neighbour(matrix[res[pos]], ini);
    res.push_back(best_pos);
  	ini.erase(ini.begin() + best_pos);
  }
}

double compute_length(vector<int> &path, vector<vector<double> > &cities){
  double result = 0;
  for(int i = 0; i < path.size()-1; i++){
    result += cities[path[i]][path[i+1]];
  }
  result += cities[0][path[path.size()-1]];
  return result;
}

int main(int argc, char **argv){

  int N; //Total number of cities
  double x, y; //Variables for data imput
  int n; //Positional argument in input data
  int next_node;
  string filename; //File that contains the input data;
  string output = "salida.tour";
  string trash;
  vector<int> ini, result; //Vector of integers representing the order of cities
  int initial;

  if(argc != 3){
    cerr << "Error in the number of arguments" << endl;
    return 1;
  }
  
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

  for(int i=0; i<N; i++){
  	ini.push_back(i);
  }
  
  greedy(ini, result, cities);
  
  //printVector(result);
  cout << "Total distance: " << compute_length(result, cities) << endl;
  ofstream out(output);
  int city;
  for(int i =0; i < result.size(); i++){
    city = result[i];
    out << city << " " << coordinates[city].first << " " << coordinates[city].second << endl;
  }


  //Obtener el grafico de la solución en el  dataset propuesto

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

  return 0;
}
