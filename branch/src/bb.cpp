//Algoritmo de branch and bound.
//Nota: No es que sea mi bebe (Looool)

#include <iostream>
#include <queue>
#include <vector>
#include <limits>
#include <cmath>
#include <fstream>
#include <stdlib.h>
#include <time.h>
//#include "genetic.cpp"
#include "nearestNeighbour.cpp"

#define dev 

using namespace std;

//============================
// Auxiliar Functions
//============================
/*void printMatrix(vector<vector<double> > &matrix){
  for(int i=0; i < matrix.size(); i++){
    for(int j=0; j < matrix[i].size(); j++){
      printf("%.4f ", matrix[i][j]);
    }
    cout << endl;
  }
}

template <typename T>
void printVector(vector<T> &v){

  cout << "[";
  for(int i =0; i < v.size()-1; i++){
    cout << v[i] << ",";
  }

  cout << v[v.size()-1];

  cout << "]";
}

//Calculate the distance between two nodes
double distance(pair<double, double> &c1, pair<double, double> &c2){
  return hypot(c2.first - c1.first, c2.second - c1.second);
}*/

//Compute length given a path. Takes 2 arguments, the path and the matrix
//with the distance between cities
/*double compute_length(vector<int> &path, vector<vector<double> > &cities){
  double result = 0;
  for(int i = 0; i < path.size()-1; i++){
    result += cities[path[i]][path[i+1]];
  }
  result += cities[path[0]][path[path.size()-1]];
  return result;
}*/

bool visitado(int c, const vector<int> &sol){
	for(int i=0; i<sol.size(); i++){
		if(sol[i]==c){
			return true;
		}
	}
	return false;
}

//Get the sum of the minimum values of each row
double sumOfMinOfEachRow(vector<int> &candidates, vector<vector<double> > &cities){

  double result = 0;

  double row_min = numeric_limits<int>::max();

  for(int i = 0; i < cities.size(); i++){
  	if(!visitado(i,candidates)){
		for(int j = i; j < cities.size(); j++){
		  if(cities[i][j] < row_min){
			row_min = cities[i][j];
		  }
		}

		result += row_min;
		row_min = numeric_limits<int>::max();
    }
  }

  return result;

}

double sumOfMinOfEachRow(vector<vector<double> > &cities){
	return sumOfMinOfEachRow(*(new vector<int>()), cities);

}

//Comparator used in priority queue

//This could be a dog
struct Comparator
{
  bool operator() (const pair<double, int> &p1, const pair<double, int> &p2 ) const {
    return p1.first < p2.first;
  }
};

//============================
// Actual code
//============================

void magic(int pos, pair<double, vector<int> > solution, vector<vector<double> > &cities, pair<double, vector<int> > &best){

  //Priority queue that contains our nodes
  //The first coordinate is the possible cost of the path and the second
  //is the actual path
  priority_queue<Comparator, vector<pair<double, int> > > alives; //I think this is how it should be
  double local_length = 0;
  pair<double, int> aux;  
  
  if(pos<solution.second.size()){
	  for (int i=1; i<solution.second.size(); i++){
	  	if(!visitado(i,solution.second)){
	  		local_length = solution.first + cities[i][solution.second[pos-1]];
	  		solution.second[pos] = i;
	  		if(local_length + sumOfMinOfEachRow(solution.second, cities) < best.first){
		  		aux.second = i;
		  		aux.first = local_length;
	  			alives.push(aux);
	  		}
	  	}
	  }
	  while(!alives.empty()){
	  	if(alives.top().first + sumOfMinOfEachRow(solution.second, cities)< best.first){
	  		solution.second[pos] = alives.top().second;
	  		solution.first = alives.top().first;
	  		magic(pos+1, solution, cities, best);
	  	}
	  	alives.pop();
	  }
  }else{
  	local_length = solution.first + cities[solution.second[pos-1]][solution.second[0]];
  	if(local_length < best.first){
	  cout << local_length << " " << best.first <<endl;
	  best = solution;
	  best.first = local_length;
	}
  }  
}


int main(int argc, char **argv){

  int N; //Total number of cities
  double x, y; //Variables for data imput
  int n; //Positional argument in input data
  int next_node;
  string filename; //File that contains the input data;
  string output = "salida/bb_";
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
  //best.first = genetic(best.second, cities);
  vector<int> ini;
  for(int i=0; i<N; i++){
  	ini.push_back(i);
  }
  greedy(ini, best.second, cities);
  best.first = compute_length(best.second, cities);

  //Algorithm
  vector<int> aux(N,0); 
  solution.first = 0;
  solution.second = aux;
  
  printVector(best.second);
  cout << best.first <<endl;
  clock_t tStart = clock();
  magic(1, solution, cities, best);
  clock_t finish = clock();

  #ifdef dev
  cout << "Ciudades: ";
  printVector(best.second);
  cout << " Total: " << best.second.size() << endl;
  cout << "Total distance: " << best.first << endl;
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
