
#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "genetic.cpp"

#define prod

double compute_length(vector<int> path, vector<vector<double> > &cities){
  double result = 0;
  for(int i = 0; i < path.size()-1; i++){
    result += cities[path[i]][path[i+1]];
  }
  result += cities[path[0]][path[path.size()-1]];
  return result;
}

bool visitado(int k, const vector<int> &v){
	for(int i = 0; i < v.size(); i++)
		if(v[i] == k)
			return true;
	return false;
}

void backtracking(int pos, pair<double, vector<int> > sol, vector<vector<double> > &cities, pair<double, vector<int> > &best){
  if(pos < cities.size()){
    for(int i = 1; i < cities.size(); i++){
  		if(!visitado(i, sol.second)){
  			sol.second[pos] = i;
        sol.first = compute_length(sol.second, cities);
  			if(sol.first < best.first)
          backtracking(pos + 1, sol, cities, best);
    	}
    }
  } else if(best.first < best.first)
    best = sol;
}

int main(int argc, char **argv){

  int N; //Total number of cities
  double x, y; //Variables for data imput
  int n; //Positional argument in input data
  int next_node;
  string filename; //File that contains the input data;
  string output = "salida/backtracking_";
  string trash;
  pair<double, vector<int> > solution; //Vector of integers representing the order of cities
  pair<double, vector<int> > best;
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
    for(int j = 0; j < i; j++){
      dist = distance(coordinates[i], coordinates[j]);
      cities[i][j] = dist;
      cities[j][i] = cities[i][j];
    }
  }

  //Use genetic
  best.first = genetic(best.second, cities);

  //Algorithm

  solution.first = 0;
  for(int i = 0; i < cities.size(); i++)
    solution.second.push_back(0);

  clock_t tStart = clock();
  backtracking(1, solution, cities, best);
  clock_t finish = clock();

  #ifdef dev
  cout << "Ciudades: ";
  printVector(best.second);
  cout << " Total: " << best.second.size() << endl;
  cout << "Total distance: " << compute_length(best.second, cities) << endl;
  #endif

  #ifdef prod
  cout << best.first << "\t" << ((double)finish - tStart)/CLOCKS_PER_SEC << endl;
  #endif

  ofstream out(output);
  int city;
  for(int i =0; i < best.second.size(); i++){
    city = best.second[i];
    out << city << " " << coordinates[city].first << " " << coordinates[city].second << endl;
  }


  //Obtener el grafico de la solución en el  dataset propuesto

  #ifdef dev
  string input = "datosTSP/";
  input += args[1] + ".opt.tour";

  ifstream archivo(input);
  vector<int> ciudades;
  int k;
  archivo >> trash;
  archivo >> k;
  for(int i =0; i < N; i++){
    archivo >> k;
    ciudades.push_back(k-1);
  }

  ofstream salida("salida/salida_suya.tour");
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
