#include <iostream>
#include <math.h>
#include <algorithm>
#include <vector>

using namespace std;


void print(vector<int> x) {
	int xsize = x.size();
	for (int i = 0; i < xsize; i++) {
		cout << x[i] << " ";
	}
	cout << endl;
}

//Class Player
class player {
private:
	vector<int> know, hold;
public:
	void init() {
		vector<int> know(0), hold(0);
	}
	void init(vector<int> x, vector<int> y) {
		know = x;
		hold = y;
		print(x);
		print(y);
	}
	vector<int> display_know() {
		return know;
	}
	vector<int> display_hold() {
		return hold;
	}
};

//Class Game
class game {
private:
	vector<int> cards;
	player p1, p2;
public:
	void init() {
		vector<int> cards(52);
		for (int i = 0; i < 13; i++) {
			cards.insert(cards.end(), 4, i + 1);
		}
		player p1, p2;
	}
	void init(vector<int> xcards, vector<int> x1, vector<int> x2) {
		cards = xcards;
		p1.init(x1, x2);
		p2.init(x2, x1);
	}
};


int main() {
	vector<int> i1 = { 1,2,3,4,5 };
	vector<int> i2 = { 3,4,5 };
	vector<int> i3 = { 1,3,5 };
	game game1;
	game1.init(i1, i2, i3);
	return 0;
}
