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

bool completo(nodo & n)
{
	if (n.vecino1 != -1 and n.vecino2 != -1)
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
			if( ( aislado(visitados[i]) and ( aislado(visitados[j]) or semiAislado(visitados[j]) ) or ( aislado(visitados[i]) and ( aislado(visitados[j]) or semiAislado(visitados[j])))))
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

		/*if(completo(visitados[nodos.first]))
			M.erase(nodos.first);
		if(completo(visitados[nodos.second]))
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
		enlazar(visitados, nodos.first, nodos.second);

		distancia_total += minimo;

		/*if(completo(visitados[nodos.first]))
			M.erase(nodos.first);
		if(completo(visitados[nodos.second]))
			M.erase(nodos.second);*/
	}

	return nodos;
}

pair<int, int> ultimaUnion(map<int, pair<double, double> > & M, vector< nodo > & visitados, const int tamanio, double & distancia_total)
{
	pair<int, int> 	nodos;
	double dist;

	for (int i = 1; i <= tamanio-1; ++i)
	{
		for (int j = i+1; j <= tamanio; ++j)
		{
			if(semiAislado(visitados[i]) and semiAislado(visitados[j]) and estaEnlazado(visitados, i, j))
			{
				dist = calculaDistacia(M[i], M[j]);
				nodos.first = i;
				nodos.second = j;
			}
		}
	}

	enlazar(visitados, nodos.first, nodos.second);
	distancia_total += dist;

	return nodos;
}

int main(int argc, char * argv[])
{
  
	map<int, pair<double, double> >  M, M_copia;
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

    M_copia = M;

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

    union_ = ultimaUnion(M, visitados, M.size(), distancia_total);
    orden.insert(union_);

/*
    for (set< pair<int, int> >::iterator it = orden.begin(); it != orden.end(); ++it)
    {
    	cout << it->first << " " << it->second << endl;
    }
*/

    //vector<int> v_secuencia;

    ofstream fs("orden_nodos.txt");

    fs << "DIMENSION: " << visitados.size()-1 << endl;

    set< pair<int, int> >::iterator it = orden.begin();
    //v_secuencia.push_back(it->first);
   // v_secuencia.push_back(it->second);

    fs << " " << it->first << " " << M_copia[it->first].first << " " << M_copia[it->first].second << endl;
	fs << " " << it->second << " " << M_copia[it->second].first << " " << M_copia[it->second].second << endl;

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
	    	fs << " " << it->second << " " << M_copia[it->second].first << " " << M_copia[it->second].second << endl;
	    	ultimo = it->second;
	    	//v_secuencia.push_back(ultimo);
    	}
	    else
	    {
	    	fs << " " << it->first << " " << M_copia[it->first].first << " " << M_copia[it->first].second << endl;
	    	ultimo = it->first;
	    	//v_secuencia.push_back(ultimo);
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
/*
	distancia_total = 0;

	for (int i = 0; i < v_secuencia.size()-1; ++i)
	{
		distancia_total += calculaDistacia(M[v_secuencia[i]], M[v_secuencia[i+1]]);
	}
*/
	fs << "DISTANCIA TOTAL: " << distancia_total << endl;

    fs.close();


    
    return 0;
} 