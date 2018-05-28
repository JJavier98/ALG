#include <iostream>
#include <fstream>
#include <cmath>
#include <fstream>
#include <stdlib.h>
#include <map>
#include <set>
#include <vector>
#include <limits>
#include <cassert>
#include <queue>
#include <chrono> 
using namespace std::chrono;

using namespace std;

const int MAX_CIUDADES = 30;
const double inf = numeric_limits<double>::infinity();
map<int, pair<double, double>> mapa_ciudades;

typedef int TDec; // Tipo Decisión

double distancias[MAX_CIUDADES][MAX_CIUDADES]; // matriz de distancias

// Función para la entrada de datos desde un archivo
void leer_datos_ciudades(ifstream & entrada, map<int, pair<double, double> > & M){
    pair<double,double> p;
    string s; 
    int n, indice_ciudad;
   
    entrada >> s; // Leo "dimension:"
    entrada >> n; // Número de ciudades
    
    int i=0;
    while (i<n) {
        entrada >> indice_ciudad >> p.first >> p.second;
        
        indice_ciudad--; // Le resto uno al índice porque empiezo a contar por la ciudad 0
        								 // en vez de por la ciudad 1
				M[indice_ciudad] = p;
				
				i++;
    }    
}

// Función para rellenar la matriz de distancias

void calcular_distancias(map<int, pair<double, double> > & mapa_ciudades, int n){
	double x1, y1, x2, y2;

	for (int i = 0; i < n; i++){
		x1 = mapa_ciudades[i].first;
		y1 = mapa_ciudades[i].second; 
	
		for (int j = 0; j < n; j++){
		
			if (i == j)
				distancias[i][j] = 0;
			else{				
				x2 = mapa_ciudades[j].first;
				y2 = mapa_ciudades[j].second;
	
				distancias[i][j] = sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) ); // Distancia euclídea
			}
		}
	}
}
/*
void ordenar_vector(vector<TDec> & v)
{
	for (int i=0; i<v.size()-1; i++)
	{
	   	for (int j=i+1; j<v.size(); j++)
	  	{
		    if(v[i]>v[j])
		    {
			    TDec aux = v[i];
			    v[i] = v[j];
			    v[j] = aux;
	    	}
	  	}
	}
}
*/
// TDA Solución
class Solucion{
private:
	int num_ciudades;
	vector<TDec> X; // Vector solución (tamaño = num_ciudades - 1)
	double distancia_actual = 0; // Distancia del camino de las ciudades visitadas
	vector<TDec> ciudades_no_visitadas; // Ciudades no visitadas todavía (elegibles para completar la solución)
public:
	void imprimir()const;
	Solucion(int numero_ciudades);
	Solucion(int numero_ciudades, double dist);
	Solucion(const Solucion & sol);
	int getNumCiudades();
	void setNumCiudades(int n);
	TDec getX(int i);
	TDec backX();
	int sizeX();
	void pushX(TDec valor);
	void popBackX();
	double getDistanciaActual();
	void setDistanciaActual(double dist);
	double calcularCotaGreedy(); // Calcula la cota greedy
   	TDec getCiudadNoVisitada(int i);
   	void pushCiudadNoVisitada(TDec ciudad);
   	int sizeCiudadesNoVisitadas();
   	void popCiudad(TDec i);
   	double calcularCotaLocal()const;
   	vector<TDec> getCiudadesNoVisitadas();
   	void algoritmo_bk(TDec ciudad);
   	void setCiudadesNO();
   	Solucion& operator=(const Solucion& sol);
};

void Solucion::setNumCiudades(int n)
{
	num_ciudades = n;
	setCiudadesNO();
}

void Solucion::setCiudadesNO()
{
	for (int i=0; i<num_ciudades;++i){
		ciudades_no_visitadas.push_back(i);	
	}
}

vector<TDec> Solucion::getCiudadesNoVisitadas()
{
	return ciudades_no_visitadas;
}

void Solucion::imprimir()const{
	cout << "DIMENSION: " << num_ciudades << endl;
	cout << "TOTAL RECORRIDO: " << distancia_actual << endl;
	for (int i=0; i<num_ciudades;++i){
		int pos = X[i]+1;
		cout << pos << " " <<mapa_ciudades[X[i]].first << " " << mapa_ciudades[X[i]].second << endl;
	}
	cout << X[0]+1 << " " <<mapa_ciudades[X[0]].first << " " << mapa_ciudades[X[0]].second << endl;
	cout << endl;
}

Solucion::Solucion(int numero_ciudades):num_ciudades(numero_ciudades)
{
	for (int i=0; i<num_ciudades;++i){
		ciudades_no_visitadas.push_back(i);	
	}
}

Solucion::Solucion(int numero_ciudades, double dist)
{
	num_ciudades = numero_ciudades;
	distancia_actual = dist;
	for (int i=0; i<num_ciudades;++i){
		ciudades_no_visitadas.push_back(i);	
	}
}

Solucion::Solucion(const Solucion & sol)
{
	num_ciudades = sol.num_ciudades;
	X = sol.X; // Vector solución (tamaño = num_ciudades - 1)
	distancia_actual = sol.distancia_actual; // Distancia del camino de las ciudades visitadas
	ciudades_no_visitadas = sol.ciudades_no_visitadas; // Ciudades no visitadas todavía (elegibles para completar la solución)
}

int Solucion::sizeX()
{
	return X.size();
}

int Solucion::getNumCiudades()
{
	return num_ciudades;
}

TDec Solucion::getX(int i)
{
	assert(i >= 0 && i < X.size());
	return X[i];
}

TDec Solucion::backX()
{
	return X.back();
}

void Solucion::pushX(TDec valor)
{
	if(X.size()==0)
		distancia_actual = 0;
	else
		distancia_actual += distancias[X.size()-1][valor];
	X.push_back(valor);
}

void Solucion::popBackX()
{
	distancia_actual -= distancias[X.size()-1][X.size()-2];
	X.pop_back();
}

double Solucion::getDistanciaActual()
{
	return distancia_actual;
}

void Solucion::setDistanciaActual(double dist)
{
	distancia_actual = dist;
}

TDec Solucion::getCiudadNoVisitada(int i)
{
	assert(i >= 0 and i < ciudades_no_visitadas.size());
	return ciudades_no_visitadas[i];
}

void Solucion::pushCiudadNoVisitada(TDec ciudad)
{
	ciudades_no_visitadas.push_back(ciudad);
}

void Solucion::popCiudad(TDec i)
{
	for(vector<TDec>::iterator it = ciudades_no_visitadas.begin() ; it != ciudades_no_visitadas.end() ; ++it)
		if(*it == i)
			ciudades_no_visitadas.erase(it);
}

int Solucion::sizeCiudadesNoVisitadas()
{
	return ciudades_no_visitadas.size();
}

Solucion& Solucion::operator=(const Solucion& sol){
	num_ciudades = sol.num_ciudades;
	X=sol.X;
	distancia_actual=sol.distancia_actual;
	ciudades_no_visitadas=sol.ciudades_no_visitadas;
	return *this;
}

double Solucion::calcularCotaLocal()const{
	double min_distancia = inf;
	vector<TDec>::const_iterator it;
	vector<TDec>::const_iterator it2;
	int ciudad_actual;
	int primera_ciudad = 0; // Primera ciudad visitada -> Por defecto, siempre la ciudad 0
	
	double cota_local = distancia_actual; // Se inicializa al valor del camino de la primera ciudad a la última visitada
	
	// Le sumo la estimación de la mínima distancia de salida desde la última ciudad visitada
	ciudad_actual = X.back(); // último elemento del vector solución
	

	for (it=ciudades_no_visitadas.begin(); it!=ciudades_no_visitadas.end(); ++it){
		if (distancias[ciudad_actual][*it] < min_distancia)
			min_distancia = distancias[ciudad_actual][*it];
	}

	cota_local += min_distancia;
	
	// Sumo a la cota local el mínimo coste de salir de cada uno las ciudades no visitadas
	for (it=ciudades_no_visitadas.begin(); it!=ciudades_no_visitadas.end(); ++it){
		ciudad_actual = *it; // Ciudad de la que estoy calculando el mínimo
		min_distancia = distancias[ciudad_actual][primera_ciudad]; // Inicializo el mínimo a la distancia entre esa ciudad y la primera (como si cerrara el circuito)
	
		for (it2=ciudades_no_visitadas.begin(); it2!=ciudades_no_visitadas.end(); ++it2){ // Mínima distancia de salida a una ciudad no visitada
			if (ciudad_actual != *it2 && distancias[ciudad_actual][*it2] < min_distancia)
				min_distancia = distancias[ciudad_actual][*it2];
		}
		
		cota_local += min_distancia;
	}

	return cota_local;
}

bool pertenece_a_vector(const vector<int>& v, int n){
	bool pertenece = false;
	for (int i=0; i<v.size() && !pertenece;++i)
		pertenece = v[i]==n;
	return pertenece;
}

double Solucion::calcularCotaGreedy(){
	Solucion mascercana(num_ciudades);
	int longitud_trayecto = 0x7FFFFFFF;
	for (int i=0; i<num_ciudades; ++i){//eleccion ciudad inicial
		int longitud=0;
		vector<int> posible;
		int ultima_ciudad=i;
		while (posible.size() != mascercana.num_ciudades){//mientras el recorrido no pase por todas las ciudades.
			int siguiente_ciudad;
			int menor_longitud = 0x7FFFFFFF;
			for (int j=0;j<num_ciudades;++j){//recorrido para escoger la siguiente ciudad a añadir.
				if (distancias[ultima_ciudad][j]<menor_longitud && ultima_ciudad!=j && !pertenece_a_vector(posible,j)){
					siguiente_ciudad=j;
					menor_longitud=distancias[ultima_ciudad][j];			
				}			
			}
			posible.push_back(siguiente_ciudad);
			longitud+=menor_longitud;
			ultima_ciudad=siguiente_ciudad;
		}
		longitud+=distancias[posible[0]][posible[posible.size()-1]];
		if (longitud<longitud_trayecto){
			mascercana.X=posible;
			mascercana.distancia_actual = longitud;		
		}
	}
	return mascercana.getDistanciaActual();
}

Solucion solucion_global(0, inf);

void Solucion::algoritmo_bk(TDec ciudad)
{
	static double cota_G = calcularCotaGreedy();

	pushX(ciudad);
	popCiudad(ciudad);

	if(calcularCotaLocal() < cota_G)
	{
		if(ciudades_no_visitadas.size()==0 and X.size() == num_ciudades)
		{
			pushX(getX(0));

			if(getDistanciaActual() < solucion_global.getDistanciaActual())
			{
				solucion_global = *this;
				cota_G = solucion_global.getDistanciaActual();
			}
		}
		else
		{
			for (int i = 0; i < sizeCiudadesNoVisitadas(); ++i)
			{
				algoritmo_bk(getCiudadNoVisitada(i));
			}
		}
	}
}

int main(int argc, char* argv[]){
	ifstream entrada;
	ofstream salida;
	int num_ciudades;
	high_resolution_clock::time_point tantes, tdespues;
	duration<long double> transcurrido;

	// Se tiene que llamar con un argumento (archivo para leer datos)
	if (argc != 2){
		cout << "Uso: " << argv[0] << " ruta_archivo_ciudades" << endl;
		return (-1);
	}

	// Abro el archivo de entrada
	entrada.open(argv[1]);
	
	if (!entrada.is_open()){
		cout << "Fallo al abrir el archivo de entrada" << endl;
		return (-2);
	}
	
	leer_datos_ciudades(entrada, mapa_ciudades);

	num_ciudades = mapa_ciudades.size();
	solucion_global.setNumCiudades(num_ciudades);
		
	if (num_ciudades < 3){
		cout << "El número de ciudades es erróneo: " << num_ciudades << endl;
		return (-3);
	}
					
	calcular_distancias(mapa_ciudades, num_ciudades); // Relleno la matriz de distancias
		
	/*for (int i = 0 ; i < num_ciudades; i++){
		for (int j = 0; j < num_ciudades; j++)
			cout << distancias[i][j] << " ";	   //IMPRIME LAS DISTANCIAS -> QUITAR
		
		cout << '\n';
	}*/

	tantes = high_resolution_clock::now();
	solucion_global.algoritmo_bk(0);

	tdespues = high_resolution_clock::now();
	transcurrido = duration_cast<duration<long double>>(tdespues - tantes);

	cout.precision(10);
	cout.setf(ios_base::fixed, ios_base::floatfield); 
	cout << "TIEMPO: " << transcurrido.count() << endl;
	solucion_global.imprimir();

		
	// Cierro los archivos
	entrada.close();
	salida.close();
	
	return 0;
}
