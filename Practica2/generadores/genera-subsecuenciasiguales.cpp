#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>

//generador de ejemplos para el problema de encontrar la subsecuencia de números iguales consecutivos de mayor longitud. Simplemente, para rellenar el vector de tamaño n genera n enteros aleatorios entre 0 y 9

double uniforme() //Genera un número uniformemente distribuido en el
                  //intervalo [0,1) a partir de uno de los generadores
                  //disponibles en C.
{
 int t = rand();
 double f = ((double)RAND_MAX+1.0);
 return (double)t/f;
}

int main(int argc, char * argv[])
{

  if (argc != 2)
    {
      cerr << "Formato " << argv[0] << " <num_elem>" << endl;
      return -1;
    }

  int n = atoi(argv[1]);

  int * T = new int[n];
  assert(T);

srand(time(0));
//para generar un vector que pueda tener elementos repetidos
for (int j=0; j<n; j++) {
  double u=uniforme();
  int k=(int)(10*u);
  T[j]=k;
}

for (int j=0; j<n; j++) {cout << T[j] << " ";}

} 
