#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

/*int TERMINACIONES = 0;*/

void printv(vector<int> &v){
	for (int i=0; i<v.size(); i++){
		cout << v[i] << " ";
	}
	cout<<endl;
}

void printm(vector<vector<int> > &m){
	for (int i=0; i<m.size(); i++){
		printv(m[i]);
	}
}

int repulsion_total(vector<int> &sol, vector<vector<int> > &conv, int tope){
	int suma=0;
	for(int i=0; i<tope; i++){
		suma += conv[sol[i]][sol[(i+1)%sol.size()]]; 
	}
	return suma;
}

bool sentado(int p, vector<int> &sol){
	for(int i=0; i<sol.size(); i++){
		if(sol[i]==p){
			return true;
		}
	}
	return false;
}

void backtracking(int pos, vector<int> sol, vector<vector<int> > &rep, vector<int> &mejor){
	if(pos<rep.size()){
	 	for(int p=0; p<rep.size(); p++){
			if(!sentado(p,sol)){
				sol[pos]=p;
				if(repulsion_total(sol,rep,pos+1)<repulsion_total(mejor,rep,rep.size()))
					backtracking(pos+1,sol,rep,mejor);
			}
		}
	}else if(repulsion_total(sol,rep,rep.size())<repulsion_total(mejor,rep,rep.size())){
		mejor = sol;
	}
}

int main(int argc, char * argv[]){

	if (argc != 2){
	  cerr << "Formato " << argv[0] << " <num_elem>" << endl;
	  return -1;
	}
	
	int n = atoi(argv[1]);
	vector<int> solucion(n,0);
	vector<int> mejor(n);
	vector<vector<int> > rep(n, vector<int>(n,0)); //Matriz simétrica con diagonal con ceros.
	
	for(int i=0; i<n; i++){
		mejor[i] = n-i-1;
	}	
	
	srand(time(NULL));
	
	for(int i=0; i<n; i++){
		for (int j=i+1; j<n; j++){
			rep[i][j] = rep[j][i] = rand() % 100;
		}
	}
	
	/*printm(rep);
	cout <<endl;
	
	cout << "Rep_total_mejor= " << repulsion_total(mejor,rep,n) <<endl;*/
	
	double tantes, tdespues;
	
	tantes = clock();	
	backtracking(1,solucion,rep,mejor);
	tdespues = clock();
	
	cout << n << " " << (tdespues - tantes)/CLOCKS_PER_SEC <<endl;
	
	/*printv(mejor);
	cout <<endl;
	cout << "Rep_total_mejor= " << repulsion_total(mejor,rep,n) <<endl;
	cout << "Terminaciones= " << TERMINACIONES <<endl;*/
	
	return 0;
}
