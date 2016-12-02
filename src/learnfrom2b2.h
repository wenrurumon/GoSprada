#include <iostream>
#include <math.h>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

void print(vector<int> x) {
	int xsize = x.size();
	for (int i = 0; i < xsize; i++) {
		cout << x[i] << " ";
	}
	cout << endl;
}

vector<int> randvec(vector<int> x_) {
	int vecsize = x_.size();
	vector<int> x = { 0 };
	for (int i = 1; i < vecsize; i++) {
		int pick = rand() % (x.size() + 1);
		x.insert(x.begin() + pick, i);
	}
	for (int i = 0; i < vecsize; i++) {
		x[i] = x_[x[i]];
	}
	return(x);
}

