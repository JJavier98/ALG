#include <iostream>
#include <cstdlib>
#include <chrono>   
    
using namespace std::chrono;
using namespace std;

// Algoritmo Secuencial
// Llega a calcular hasta el número 2146687710 -> 1289 * 1290 * 1291

// Devuelve el primero de los 3 números, en caso de poder expresarse en términos de ese producto,
// y 0 en caso contrario

unsigned long productoTresNumeros(unsigned long numero){
	int producto = 0;
	int i;
	for (i = 1 ; producto < numero ; ++i)
	{
		producto = i * (i+1) * (i+2);
	}
	if (producto == numero)
	{
		return --i;
	}
	else
	{
		return 0;
	}
}

int main (int argc, char* argv[]){

	if (argc != 2){
		cout << "Uso: " << argv[0] << " numero a expresar como producto de 3 número consecutivos\n";
		return (-1);
	}

	unsigned long numero = atol(argv[1]);
	
	high_resolution_clock::time_point tantes, tdespues;
	duration<long double> transcurrido;

	tantes = high_resolution_clock::now();
	
	unsigned long primer_numero = productoTresNumeros(numero);
	
	tdespues = high_resolution_clock::now();
	transcurrido = duration_cast<duration<long double>>(tdespues - tantes);
	
	cout.precision(10);
	cout.setf(ios_base::fixed, ios_base::floatfield); // Hago que evite la notación científica
	
	if (primer_numero == 0)
		cout << numero << ' ' << primer_numero << ' ' << transcurrido.count() << endl;
	else
		cout << numero << ' ' << primer_numero << ' ' << primer_numero+1 << ' ' << 
			primer_numero+2 << ' ' << transcurrido.count() << endl;
}
