#include <iostream>
#include <fstream>
#include <cmath>
#include <fstream>
#include <stdlib.h>
#include <map>
#include <set>
#include <vector>
#include <limits>

using namespace std;

const int MAX_CIUDADES = 30;
const double inf = std::numeric_limits<double>::infinity();

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

typedef int TDec; // Tipo Decisión

// TDA Solución
class Solucion{
private:
	const int num_ciudades;
	vector<TDec> X; // Vector solución (tamaño = num_ciudades - 1)
	double distancia_actual; // Distancia del camino de las ciudades visitadas
	set<TDec> ciudades_no_visitadas; // Ciudades no visitadas todavía (elegibles para completar la solución)
	double calcularCotaLocal(); // Calcula la cota local del nodo
	double cota_bk;
public:
	Solucion(int numero_ciudades);
	bool cumpleRestImp(); // Comprueba que no se visita una ciudad más de una vez
	bool cumpleCotas(double cota_global); // Comprueba que la cota local es menor que la global (llama al método CalcularCotaLocal)
	bool esSolucion(); // Devuelve true si el nodo es un nodo solución (vector solución lleno)
	bool operator<(Solucion& sol);
	bool hayMasValores();
	void siguienteValor();
   Solucion algoritmo_b_y_b();
   Solucion algoritmo_bk();
};

Solucion::Solucion(int numero_ciudades, double distancia):num_ciudades(numero_ciudades){
	distancia_actual=distancia;
}

double Solucion::calcularCotaLocal(){
	double min_distancia = INFINITY;
	set<TDec>::iterator it;
	set<TDec>::iterator it2;
	TDec ciudad_actual;
	TDec primera_ciudad = 0; // Primera ciudad visitada -> Por defecto, siempre la ciudad 0
	
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

bool Solucion::operator<(Solucion& sol){
	if (calcularCotaLocal()<sol.calcularCotaLocal())
		return true;
	else
		return false;
}

bool Solucion::cumpleRestImp(){
	bool cumple=false;

}

bool Solucion::cumpleCotas(double cota_global){
	return calcularCotaLocal()<cota_global;
}

bool Solucion::esSolucion(){
	bool esSol = false;
	if (X.size()==num_ciudades && cumpleRestImp())
		esSol=true;
	return esSol;
}

bool Solucion::hayMasValores(){
	return !ciudades_no_visitadas.empty() && X[X.size()-1]!=num_ciudades-1;
}

void Solcion::siguienteValor(){
	if (X[X.size()-1]==num_ciudades-1){}
	else{}
}

Solucion Solucion::algoritmo_b_y_b(){
	priority_queue<Solucion, vector<Solucion>, less<Solulcion> > cola;
	Solucion nodo_a_explorar (), mejor_solucion ();
	double cota_global = ;
	cola.push (nodo_a_explorar);

	while(!cola.empty() && (cola.top().cumpleCotas())){
		nodo_a_explorar=cola.top();
		cola.pop();
		while (nodo_a_explorar.hayMasValores()){
			if (nodo_a_explorar.esSolucion() && distancia_actual<cota_global){
				cota_global = distancia_actual;
				mejor_solucion=nodo_a_explorar;
			}
			else if (nodo_a_explorar.cumpleCotas() && nodo_a_explorar.cumpleRestImp()){
				cola.push(nodo_a_explorar);
			}
			nodo_a_explorar.siguienteValor();
		}
	}	
	return mejor_solucion
}

Solucion Solucion::algoritmo_bk()
{
	for (int i = 0; i < ciudades_no_visitadas.size(); ++i)
	{
		
	}
}

int main(int argc, char* argv[]){
	ifstream entrada;
	ofstream salida;
	map<int, pair<double, double>> mapa_ciudades; // Primera ciudad es mapa_ciudades[0]
	int num_ciudades;

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
		
	// Cierro los archivos
	entrada.close();
	salida.close();
	
	return 0;
}
