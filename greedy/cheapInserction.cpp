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


void printMatrix(vector<vector<double>> matrix){
  for(int i=0; i < matrix.size(); i++){
    for(int j=0; j < matrix[i].size(); j++){
      printf("%.4f ", matrix[i][j]);
    }
    cout << endl;
  }
}

template <typename T>
void printVector(vector<T> v){

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

int closest_element(int pos, vector<double> v){
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

double compute_addition(int p1, int p2, int p3, vector<vector<double>>&matrix){
  return matrix[p3][p1] + matrix[p2][p3] - matrix[p1][p2];
}

vector<int> add_closet_to_path(vector<int> path, int N, vector<vector<double>>& matrix){
  double best_dist = numeric_limits<double>::max();
  double dist;
  int best_pos=0;
  vector<int> new_path(path);
  
  //For every city
  for(int city=0; city < N; city++){
    //Check if it's already in the path
    if(find(new_path.begin(), new_path.end(), city) == new_path.end()){
      //If not in the path for every city
      for(int j=0; j < new_path.size()-1; ++j){
	dist = compute_addition(new_path[j+1], new_path[j], city, matrix);
	//Test if is the best match
	if (dist <= best_dist){
	  best_dist = dist;
	  best_pos = j;
	}
      }
      new_path.insert(new_path.begin()+best_pos, city);
    }
  }

  return new_path;
}

double compute_length(vector<int> path, vector<vector<double>> &cities){
  double result = 0;
  for(int i = 0; i < path.size()-1; i++){
    result += cities[path[i]][path[i+1]];
  }
  result += cities[0][path[path.size()]];
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
  vector<int> result; //Vector of integers representing the order of cities
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

  vector<pair<double, double>> coordinates;
  
  //Create an square matrix
  vector<vector<double>> cities(N, vector<double>(N,0));

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

  //Start with a random node
  //srand (time(NULL));
  //initial = rand()%(N);
  result.push_back(mini);

  //Search for the nearest node and add it to the circuit
  //int latest = result[result.size()-1];
  //next_node = closest_element(latest, cities[latest]);
  result.push_back(minj);

  result = add_closet_to_path(result,N, cities);

  printVector(result);
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
