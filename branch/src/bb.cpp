//Algoritmo de branch and bound.
//Nota: No es que sea mi bebe

#include <iostream>
#include <queue>
#include <vector>
#include <limits>

//============================
// Auxiliar Functions
//============================
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

//Calculate the distance between two nodes
double distance(pair<double, double> c1, pair<double, double> c2){
  return hypot(c2.first - c1.first, c2.second - c1.second);
}

//Compute length given a path. Takes 2 arguments, the path and the matrix
//with the distance between cities
double compute_length(vector<int> path, vector<vector<double> > &cities){
  double result = 0;
  for(int i = 0; i < path.size()-1; i++){
    result += cities[path[i]][path[i+1]];
  }
  result += cities[path[0]][path[path.size()-1]];
  return result;
}

//Get the sum of the minimum values of each row
double sumOfMinOfEachRow(vector<vector<double> > &cities){

  double result = 0;

  double row_min = numeric_limits<int>::max();

  for(int i = 0; i < cities.size(); i++){
    for(int j = 0; j < cities.size(); j++){
      if(cities[i][j] < row_min){
	row_min = cities[i][j];
      }
    }

    result += row_min;
    row_min = numeric_limits<int>::max();
  }

  return result;

}

//Comparator used in priority queue

//This could be a dog
struct Comparator
{
  bool operator() (const pair<int, vector<int> &p1, const pair<int, vector<int> &p2 ) const {
    return p1.first < p2.first;
  }
};



//============================
// Actual code
//============================

void magic(vector<int> solution, vector<vector<double> > &cities){

  //Priority queue that contains our nodes
  //The first coordinate is the possible cost of the path and the second
  //is the actual path
  priority_queue<Comparator, vector<pair<int, vector<int> > > > tree; //I think this is how it should be
  int minimum_cost = numeric_limits<int>::max();

  
  
}


int main(int argc, char **argv){

  
  int N; //Total number of cities
  double x, y; //Variables for data imput
  int n; //Positional argument in input data
  string filename; //File that contains the input data;
  string output = "salida/bb_";
  string trash;
  vector<int> solution; //Vector of integers representing the order of cities
  int initial;
  double dist;


  std::vector<std::string> args;
  std::copy(argv + 1, argv + argc, std::back_inserter(args));

  //Open the file
  filename = argv[1];
  ifstream data(filename);
  data >> trash;
  data >> N; //First line is always the cardinal of cities

  //Create an square matrix
  vector<vector<double> > cities(N, vector<double>(N,0));

  //Store all the input data
  for(int i=0; i < N; i++){
    data >> n >> x >> y;
    coordinates.push_back({x,y});
  }

  for(int i = 0; i < N; i++){
    for(int j=0; j <= i; j++){
      dist = distance(coordinates[i], coordinates[j]);
      cities[i][j] = dist;
      cities[j][i] = cities[i][j];
    }
  }

  magic(solution, cities);

  
}
