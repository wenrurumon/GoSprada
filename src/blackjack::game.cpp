#include <iostream>
#include <math.h>
#include <algorithm>
#include <vector>
#include "Header.h"

using namespace std;

int main() {
	vector<int> i1;
	for (int i = 0; i < 13; i++) {
		i1.insert(i1.end(), 4, i + 1);
	}
	vector<int> i2,i3;
	game game1;
	game1.init(i1,i2,i3);
	vector<int> pushcard = { 1,2,1,2,1,2,1 };
	game1.display();
	for (int i = 0; i < pushcard.size(); i++) {
		game1.licence(pushcard[i]);
		game1.display();
		game1.end();
	}


	return 0;
}
