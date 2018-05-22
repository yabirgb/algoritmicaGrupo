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
#include "genetic.cpp"
//#include "nearestNeighbour.cpp"

#define prod 

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

//Get the sum of the minimum values of each not-used row
double estimacion(vector<int> &candidates, vector<vector<double> > &cities){

  double result = 0;
  double row_min = numeric_limits<int>::max();

  for(int i = 0; i < cities.size()-1; i++){
  	if(!visitado(i,candidates)){
		for(int j = i+1; j < cities.size(); j++){
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

//Get the sum of the minimum values of each row
double estimacion(vector<vector<double> > &cities){
	return estimacion(*(new vector<int>()), cities);

}

//Comparator used in priority queue

//This could be a dog
struct Comparator
{
  bool operator() (const pair<double, vector<int> > &p1, const pair<double, vector<int> > &p2 ) const {
    return p1.first < p2.first;
  }
};

int farthest(vector<pair<double, double> > &coordinates){
  pair<double,double> centro(0,0);
  double dist, max = 0;
  int mejor = 0;

  for(int i = 0; i < coordinates.size(); i++){
	centro.first += coordinates[i].first;
	centro.second += coordinates[i].second;
  }
  
  centro.first /= coordinates.size();
  centro.second /= coordinates.size();
  
  for(int i = 0; i < coordinates.size(); i++){
     dist = distance(coordinates[i], centro);
     if(dist > max){
     	max = dist;
     	mejor = i;
     }
  }

  return mejor;
}

//============================
// Actual code
//============================

void magic(priority_queue<Comparator, vector<pair<double, vector<int> > > > &alives, vector<vector<double> > &cities, pair<double, vector<int> > &best){

  //Priority queue that contains our nodes
  //The first coordinate is the possible cost of the path and the second
  //is the actual path
  
 pair<double, vector<int> > solution = alives.top();	//Toma el primero de la cola
 double local_length = solution.first;					//Guardamos la distancia actual recorrida
 alives.pop(); 											//Quitamos el elemento de la cima
 
  if(solution.second.size() == cities.size()){			//Si es una hoja, le añade el último arco (hacia el inicio)
  	local_length += cities[solution.second[solution.second.size()-1]][solution.second[0]];
  }
  
  if(local_length < best.first){					//Si sobrepasa la cota se poda el nodo (se ignora)
	  if(solution.second.size() < cities.size()){	// Si no es una hoja, desarrolla los nodos hijos (si 
		  for (int i=1; i<cities.size(); i++){		//tienen una estimación válida)
		  	if(!visitado(i,solution.second)){
		  		pair<double, vector<int> > aux(solution);
		  		local_length = aux.first + cities[i][aux.second[aux.second.size()-1]];
			  	aux.first = local_length;
		  		aux.second.push_back(i);
		  		
		  		if(local_length + estimacion(aux.second, cities) < best.first){	//Comprueba si merece la pena explorarlo
			  		aux.first = local_length;
		  			alives.push(aux);
		  		}
		  	}
		  }
	  }else{										//Si es una hoja, reemplaza la mejor solución
	  	  ///////////////Comprobación temporal//////////////////
	  	  cout << local_length << " " << best.first <<endl;
	  	  //////////////////////////////////////////////////////
		  best = solution;
		  best.first = local_length;
	  } 
  } 
}


int main(int argc, char **argv){

  int N; //Total number of cities
  int n; //Positional argument in input data
  int next_node, initial;
  double x, y; //Variables for data imput
  double dist;
  string trash, filename, output = "salida/bb_";
  pair<double, vector<int> > solution; //Vector of integers representing the order of cities
  pair<double, vector<int> > best;	//Best solution

  if(argc > 3){
    cerr << "Error in the number of arguments" << endl;
    return 1;
  }
  
  vector<string> args;
  copy(argv + 1, argv + argc, back_inserter(args));
  output += args[1] + ".tour";

  //Open the file
  filename = argv[1];
  ifstream data(filename);
  data >> trash;
  data >> N; //First line is always the cardinal of cities

  //Create a vector of pairs
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
	cout << "Longitud: " << best.first << endl;
  //Use greedy
  /*vector<int> ini;
  for(int i=0; i<N; i++){
  	ini.push_back(i);
  }
  greedy(ini, best.second, cities);
  best.first = compute_length(best.second, cities);*/

  //Algorithm
  priority_queue<Comparator, vector<pair<double, vector<int> > > > alives;	//Creates the priority queue
  alives.push({farthest(coordinates),{0}});
  vector<int> aux(N,0); 
  solution.first = 0;
  solution.second = aux;
  
  //Execution
  clock_t tStart = clock();
  while(!alives.empty()){
  	magic(alives, cities, best);
  }
  clock_t finish = clock();
  //

  //Shows some development data
  #ifdef dev
  cout << "Ciudades: ";
  printVector(best.second);
  cout << " Total: " << best.second.size() << endl;
  cout << "Total distance: " << compute_length(best.second, cities) << endl;
  #endif
  
  //Shows the execution time
  #ifdef prod
  cout << best.first << "\t" << ((double)finish - tStart)/CLOCKS_PER_SEC << endl;	//Shows the execution time
  #endif

  //Creates the output file
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
