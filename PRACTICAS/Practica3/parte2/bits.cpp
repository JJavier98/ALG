#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <climits>

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main(int argc, char const *argv[])
{
	vector<int> v;

	for (int i = 0; i < 16; ++i)
	{
		v.push_back(0);
	}

	v[15] = v[15] | 1<<4;
	v[15] = v[15] | 1<<10;

	for (int i = 0; i < 16; ++i)
	{
		cout << v[i] << endl;
	}
	int x = v[15] & 1<<4;
		x = x>>4;

		if(x==1)
			cout << "enlazado con 4" << endl;

	int y = 2 | 4;
	cout << y <<endl;
	return 0;
}