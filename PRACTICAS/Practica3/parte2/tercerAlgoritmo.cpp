#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <climits>

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

struct nodo{
	int num 	= -1;
	int vecino1 = -1;
	int vecino2 = -1;
	int grafo	= -1;
};


bool aislado(const nodo & n)
{
	if(n.vecino1 == -1 and n.vecino2 == -1)
		return true;
	else
		return false;
}

void enlazar(vector< nodo > & visitados, int pos, int marca, int num_grafo, map<int, unordered_set<nodo> > & sub_g)
{
	if(visitados[pos].vecino1 == -1)
		visitados[pos].vecino1 = visitados[marca].num;
	else
		visitados[pos].vecino2 = visitados[marca].num;

	if(visitados[marca].vecino1 == -1)
		visitados[marca].vecino1 = visitados[pos].num;
	else
		visitados[marca].vecino2 = visitados[pos].num;


	if(visitados[pos].grafo == -1 and visitados[marca].grafo == -1)
	{
		visitados[pos].grafo = num_grafo;
		visitados[marca].grafo = num_grafo;
		sub_g[num_grafo].insert(visitados[pos]);
		sub_g[num_grafo].insert(visitados[marca]);
	}
	else if(visitados[pos].grafo != -1 and visitados[marca].grafo == -1)
	{
		visitados[marca].grafo = visitados[pos].grafo;
		sub_g[visitados[pos].grafo].insert(visitados[marca]);
	}
	else if(visitados[marca].grafo != -1 and visitados[pos].grafo == -1)
	{
		visitados[pos].grafo = visitados[marca].grafo;
		sub_g[visitados[marca].grafo].insert(visitados[pos]);
	}
	else if(visitados[pos].grafo != -1 and visitados[marca].grafo != -1)
	{
		int a_borrar = visitados[marca].grafo;

		for(set<nodo>::iterator it = sub_g[a_borrar].begin() ; it != sub_g[a_borrar].end() ; ++it)
		{
			it->grafo = visitados[pos].grafo;
			sub_g[visitados[pos].grafo].insert(*it);
		}

		sub_g.erase(a_borrar);
	}
}

bool estaEnlazado(const vector< nodo > & visitados, int pos, int marca)
{
	if(visitados[pos].grafo == visitados[marca].grafo)
		return true;
	else
		return false;
}

void leer_puntos(string & nombre, map<int, pair<double, double> > & M){
    ifstream datos;
    string s;
    pair<double,double> p;
    int n,act;
    
    
    datos.open(nombre.c_str());
    if (datos.is_open()) {
    datos >> s; // Leo "dimension:"
    datos >> n;
    int i=0;
    while (i<n) {
        datos >> act >> p.first >> p.second;
	M[act] = p;
	i++;
      }
       
    datos.close();
    }
   else { 
      cout << "Error de Lectura en " << nombre << endl;
    }
 }

double calculaDistacia(const pair<double, double> & a, const pair<double, double> & b)
{
	double x = abs(a.first-b.first);
	double y = abs(a.second-b.second);
	double x2 = x*x;
	double y2 = y*y;

	return sqrt(x2+y2);
}

bool semiAislado(const nodo & n)
{
	if(n.vecino1 != n.vecino2 and (n.vecino1 == -1 or n.vecino2 == -1) )
		return true;
	else
		return false;
}

pair<int, int> caminoMinimo(map<int, pair<double, double> > & M, vector< nodo > & visitados, const int tamanio, int num_grafo, map<int, unordered_set<nodo> > & sub_g)
{
	pair<int, int> nodos;
	double minimo = INT_MAX;
	bool haEntrado = false;

	for (int i = 0; i < tamanio-1; ++i)
	{
		for (int j = i+1; j < tamanio; ++j)
		{
			if(aislado(visitados[i]) or aislado(visitados[j]))
			{
				double dist = calculaDistacia(M[i], M[j]);
				if(dist < minimo)
				{
					haEntrado = true;
					minimo = dist;
					nodos.first = i;
					nodos.second = j;
				}
			}
		}
	}

	if(!haEntrado)
		nodos = {-1,-1};
	else
	{
		enlazar(visitados, nodos.first, nodos.second, num_grafo, sub_g);

		/*if(pop_count(visitados[nodos.first]) == 2)
			M.erase(nodos.first);
		if(pop_count(visitados[nodos.second]) == 2)
			M.erase(nodos.second);*/
	}

	return nodos;
}

pair<int, int> unirSubgrafos(map<int, pair<double, double> > & M, vector< nodo > & visitados, const int tamanio, map<int, unordered_set<nodo> > & sub_grafos)
{
	pair<int, int> 	nodos;
	double 			minimo = INT_MAX;
	bool 			haEntrado = false;

	for (int i = 0; i < tamanio-1; ++i)
	{
		for (int j = i+1; j < tamanio; ++j)
		{
			if(semiAislado(visitados[i]) and semiAislado(visitados[j]) and !estaEnlazado(visitados, i, j))
			{
				double dist = calculaDistacia(M[i], M[j]);
				if(dist < minimo)
				{
					haEntrado = true;
					minimo = dist;
					nodos.first = i;
					nodos.second = j;
				}
			}
		}
	}

	if(!haEntrado)
		nodos = {-1,-1};
	else
	{
		enlazar(visitados, nodos.first, nodos.second, tamanio, sub_grafos);

		/*if(pop_count(visitados[nodos.first]) == 2)
			M.erase(nodos.first);
		if(pop_count(visitados[nodos.second]) == 2)
			M.erase(nodos.second);*/
	}

	return nodos;
}

int main(int argc, char * argv[])
{
  
	map<int, pair<double, double> >  M;
	map<int, unordered_set<nodo> > sub_grafos;
	vector< nodo > visitados;
	set< pair<int, int> > orden;
	string fp;

	if (argc != 2)
	{
		cout << "Error Formato:  tsp puntos" << endl;
		exit(1);
	}
   
    fp = argv[1];
    leer_puntos(fp, M);


    visitados.reserve(M.size());
    for (int i = 0; i < M.size(); ++i)
    {
    	nodo n;
    	n.num = i;
    	visitados.push_back(n);
    }
    
	int i = 0;
    pair<int, int> camino = caminoMinimo(M, visitados, visitados.size(), i, sub_grafos);
    ++i;

    while(camino.first != -1)
    {
    	orden.insert(camino);
    	camino = caminoMinimo(M, visitados, visitados.size(), i, sub_grafos);
    	++i;
    }

    pair<int, int> union_ = unirSubgrafos(M, visitados, M.size(), sub_grafos);

    while(union_.first != -1)
    {
    	orden.insert(union_);
    	union_ = unirSubgrafos(M, visitados, M.size(), sub_grafos);
    }

    ofstream fs("orden_nodos.txt");

    fs << "DIMENSION: " << visitados.size() << endl;

    for (set< pair<int, int> >::iterator it = orden.begin(); it != orden.end(); ++it)
    {
    	fs << it->first << " " << it->second << endl;
    }
    fs.close();


    
    return 0;
} 