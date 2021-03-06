#include <iostream>
#include <cstdlib>
#include <vector>
#include <time.h>

using namespace std;

int calcula_max(vector<int> &v, int inicio, int final)
{
	int max = v[inicio];
	for(int i = inicio+1 ; i < final ; ++i)
	{
		if(v[i] > max)
			max = v[i];
	}
	return max;
}

int max(int a, int b)
{
	if(a > b)
		return a;
	else
		return b;
}

int calcula_max_dyv(vector<int> &v, int inicio, int final)
{
	if(final-inicio>10)
	{
		int a = calcula_max_dyv(v, inicio, (inicio+final)/2);
		int b = calcula_max_dyv(v, (inicio+final)/2, final);
		return max(a,b);
	}
	else
		return calcula_max(v, inicio, final);
}

int main(int argc, char const *argv[])
{
	if (argc != 2)
    {
      cerr << "Formato " << argv[0] << " <num_elem>" << endl;
      return -1;
    }

  	int n = atoi(argv[1]);

	struct timespec cgt1,cgt2;
	vector<int> v;
	
	for(int i = 0 ; i < n ; ++i)
		v.push_back(i);
	

	clock_gettime(CLOCK_REALTIME,&cgt1);

	calcula_max_dyv(v, 0, v.size());

	clock_gettime(CLOCK_REALTIME,&cgt2);

	double ncgt1=(double) (cgt2.tv_sec-cgt1.tv_sec) + (double) ((cgt2.tv_nsec-cgt1.tv_nsec)/(1.e+9));

	cout << ncgt1 << endl;
	
	return 0;
}