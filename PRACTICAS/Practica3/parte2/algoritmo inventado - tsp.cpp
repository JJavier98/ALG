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
};


bool aislado(const nodo & n)
{
	if(n.vecino1 == -1 and n.vecino2 == -1)
		return true;
	else
		return false;
}

void enlazar(vector< nodo > & visitados, int pos, int marca)
{
	if(visitados[pos].vecino1 == -1)
		visitados[pos].vecino1 = marca;
	else if(visitados[pos].vecino2 == -1)
		visitados[pos].vecino2 = marca;

	if(visitados[marca].vecino1 == -1)
		visitados[marca].vecino1 = pos;
	else if(visitados[marca].vecino2 == -1)
		visitados[marca].vecino2 = pos;
}

bool estaEnlazado(const vector< nodo > & visitados, int pos, int marca)
{
	bool encontrado = false;

	if(aislado(visitados[pos]) or aislado(visitados[marca]) )
		encontrado = false;
	else
	{
		if(visitados[pos].vecino1 == marca or visitados[pos].vecino2 == marca)
			encontrado = true;
		else
		{
			int pos_nueva = visitados[pos].vecino1;
			int pos_antigua = pos;

			while(visitados[pos_nueva].vecino1 != -1 and
				visitados[pos_nueva].vecino2 != -1 and
				!encontrado and pos_nueva != -1)
			{
				if(visitados[pos_nueva].vecino1 == marca or visitados[pos_nueva].vecino2 == marca)
					encontrado = true;
				else
				{
					if(visitados[pos_nueva].vecino1 != pos_antigua)
					{
						pos_antigua = pos_nueva;
						pos_nueva = visitados[pos_nueva].vecino1;
					}
					else if(visitados[pos_nueva].vecino2 != pos_antigua)
					{
						pos_antigua = pos_nueva;
						pos_nueva = visitados[pos_nueva].vecino2;
					}
					else
						pos_nueva = -1;
				}
			}

			if(!encontrado)
			{
				pos_nueva = visitados[pos].vecino2;
				pos_antigua = pos;

				while(visitados[pos_nueva].vecino1 != -1 and
				visitados[pos_nueva].vecino2 != -1 and
				!encontrado and pos_nueva != -1)
				{
					if(visitados[pos_nueva].vecino1 == marca or visitados[pos_nueva].vecino2 == marca)
						encontrado = true;
					else
					{
						if(visitados[pos_nueva].vecino1 != pos_antigua)
						{
							pos_antigua = pos_nueva;
							pos_nueva = visitados[pos_nueva].vecino1;
						}
						else if(visitados[pos_nueva].vecino2 != pos_antigua)
						{
							pos_antigua = pos_nueva;
							pos_nueva = visitados[pos_nueva].vecino2;
						}
						else
							pos_nueva = -1;
					}
				}
			}
		}
	}
	return encontrado;
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
    while (i<=n) {
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

pair<int, int> caminoMinimo(map<int, pair<double, double> > & M, vector< nodo > & visitados, const int tamanio, double & distancia_total)
{
	pair<int, int> nodos;
	double minimo = INT_MAX;
	bool haEntrado = false;

	for (int i = 1; i <= tamanio-1; ++i)
	{
		for (int j = i+1; j <= tamanio; ++j)
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
		enlazar(visitados, nodos.first, nodos.second);

		distancia_total += minimo;

		/*if(pop_count(visitados[nodos.first]) == 2)
			M.erase(nodos.first);
		if(pop_count(visitados[nodos.second]) == 2)
			M.erase(nodos.second);*/
	}

	return nodos;
}

pair<int, int> unirSubgrafos(map<int, pair<double, double> > & M, vector< nodo > & visitados, const int tamanio, double & distancia_total)
{
	pair<int, int> 	nodos;
	double 			minimo = INT_MAX;
	bool 			haEntrado = false;

	for (int i = 1; i <= tamanio-1; ++i)
	{
		for (int j = i+1; j <= tamanio; ++j)
		{
			if(semiAislado(visitados[i]) and semiAislado(visitados[j]) /*and !estaEnlazado(visitados, i, j)*/)
			{
				if(!estaEnlazado(visitados, i, j))
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
	}

	if(!haEntrado)
		nodos = {-1,-1};
	else
	{
		enlazar(visitados, nodos.first, nodos.second);

		distancia_total += minimo;

		/*if(pop_count(visitados[nodos.first]) == 2)
			M.erase(nodos.first);
		if(pop_count(visitados[nodos.second]) == 2)
			M.erase(nodos.second);*/
	}

	return nodos;
}

pair<int, int> ultimaUnion(map<int, pair<double, double> > & M, vector< nodo > & visitados, const int tamanio)
{
	pair<int, int> 	nodos;

	for (int i = 1; i <= tamanio-1; ++i)
	{
		for (int j = i+1; j <= tamanio; ++j)
		{
			if(semiAislado(visitados[i]) and semiAislado(visitados[j]) and estaEnlazado(visitados, i, j))
			{
				nodos.first = i;
				nodos.second = j;
			}
		}
	}

	enlazar(visitados, nodos.first, nodos.second);

	return nodos;
}

int main(int argc, char * argv[])
{
  
	map<int, pair<double, double> >  M;
	vector< nodo > visitados;
	set< pair<int, int> > orden;
	string fp;
	double distancia_total = 0;

	if (argc != 2)
	{
		cout << "Error Formato:  tsp puntos" << endl;
		exit(1);
	}
   
    fp = argv[1];
    leer_puntos(fp, M);

    visitados.reserve(M.size());
    nodo null;
    visitados.push_back(null);
    for (int i = 1; i <= M.size(); ++i)
    {
    	nodo n;
    	n.num = i;
    	visitados.push_back(n);
    }

    pair<int, int> camino = caminoMinimo(M, visitados, visitados.size(), distancia_total);
    while(camino.first != -1)
    {
    	orden.insert(camino);
    	camino = caminoMinimo(M, visitados, visitados.size(), distancia_total);
    }

    pair<int, int> union_ = unirSubgrafos(M, visitados, M.size(), distancia_total);
    while(union_.first != -1)
    {
    	orden.insert(union_);
    	union_ = unirSubgrafos(M, visitados, M.size(), distancia_total);
    }

    union_ = ultimaUnion(M, visitados, M.size());
    orden.insert(union_);


    ofstream fs("orden_nodos.txt");

    fs << "DIMENSION: " << visitados.size()-1 << endl;

    set< pair<int, int> >::iterator it = orden.begin();

    fs << " " << it->first << " " << M[it->first].first << " " << M[it->first].second << endl;
	fs << " " << it->second << " " << M[it->second].first << " " << M[it->second].second << endl;

	int ultimo = it->second;
	orden.erase(it);
    it = orden.begin();
    bool salir = false;
    if(it==orden.end())
    	salir = true;

    while(it->first != ultimo and it->second != ultimo and it != orden.end() and !salir)
    {
    	++it;
    }

    if(it==orden.end())
    	salir = true;

    while(orden.size()>0 and !salir)
    {
    	if(ultimo == it->first)
    	{
	    	fs << " " << it->second << " " << M[it->second].first << " " << M[it->second].second << endl;
	    	ultimo = it->second;
    	}
	    else
	    {
	    	fs << " " << it->first << " " << M[it->first].first << " " << M[it->first].second << endl;
	    	ultimo = it->first;
	    }

		orden.erase(it);

	    it = orden.begin();

	    while(it->first != ultimo and it->second != ultimo and it != orden.end())
	    {
	    	++it;
	    }

	    if(it==orden.end())
    		salir = true;
	}

	fs << "DISTANCIA TOTAL: " << distancia_total << endl;

    fs.close();


    
    return 0;
} 