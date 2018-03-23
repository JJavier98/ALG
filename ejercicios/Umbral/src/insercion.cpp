#include <iostream>

#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <chrono>
using namespace std;
using namespace std::chrono;

static void insercion_lims(int T[], int inicial, int final)
{
  int i, j;
  int aux;
  for (i = inicial + 1; i < final; i++) {
    j = i;
    while ((T[j] < T[j-1]) && (j > 0)) {
      aux = T[j];
      T[j] = T[j-1];
      T[j-1] = aux;
      j--;
    };
  };
}

inline static void insercion(int T[], int num_elem)
{
  insercion_lims(T, 0, num_elem);
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
  high_resolution_clock::time_point tantes, tdespues;
  duration<double> transcurrido = duration<double>(0.0);
  srandom(time(0));

  for (int j = 0; j<5; j++){

    for (int i = 0; i < n; i++)
     {
       T[i] = random();
     }
    tantes = high_resolution_clock::now();
    insercion(T, n);
      tdespues = high_resolution_clock::now();
    transcurrido += duration_cast<duration<double>>(tdespues-tantes); 
  }
  
  transcurrido = transcurrido/5.0;
  cout.setf(ios_base::fixed, ios_base::floatfield);
  cout << transcurrido.count() << '\n';
  delete [] T;

  return 0;
};