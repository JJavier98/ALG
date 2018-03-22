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
	int a = calcula_max(v, inicio, final/2);
	int b = calcula_max(v, final/2+1, final);
	if(a > b)
		return a;
	else
		return b;
}

int main(int argc, char const *argv[])
{
	struct timespec cgt1,cgt2;
	vector<int> v;

	/*
	srand(time(NULL));
	for(int i = 0 ; i < 100 ; ++i)
		v.push_back(rand() % 100);
	*/

	
	for(int i = 0 ; i < 500 ; ++i)
		v.push_back(i);
	

	clock_gettime(CLOCK_REALTIME,&cgt1);

	calcula_max(v, 0, v.size());

	clock_gettime(CLOCK_REALTIME,&cgt2);

	//cout << calcula_max_dyv(v, 0, v.size()) << endl;
	//cout << calcula_max(v) << endl;

	double ncgt=(double) (cgt2.tv_sec-cgt1.tv_sec) + (double) ((cgt2.tv_nsec-cgt1.tv_nsec)/(1.e+9));

	cout << ncgt << endl;
	
	return 0;
}