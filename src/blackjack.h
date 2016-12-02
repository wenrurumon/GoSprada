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
		if (know.size() > 0) {
			know.erase(know.begin() + 0);
		}

	}
	void display() {
		cout << "KNOW" << endl;
		print(know);
		cout << "HOLD" << endl;
		print(hold);
	}
	vector<int> holdval() {
		return hold;
	}

};

//Class Game
class game {
private:
	vector<int> cards;
	player p1, p2;
public:
	void init(vector<int> xcards, vector<int> x1, vector<int> x2) {
		cards.clear();
		cards = xcards;
		p1.init(x1, x2);
		p2.init(x2, x1);
	}
	void display() {
		cout << "CARDS" << endl;
		print(cards);
		cout << "P1" << endl;
		p1.display();
		cout << "P2" << endl;
		p2.display();
	}
	void licence(int p) {
		int cardsize = cards.size();
		int pick = rand() % cardsize;
		int pickval = cards[pick];
		cards.erase(cards.begin() + pick);

		vector<int> h1 = p1.holdval();
		vector<int> h2 = p2.holdval();

		if (p == 1) {
			h1.insert(h1.end(), 1, pickval);
		}
		else {
			h2.insert(h2.end(), 1, pickval);
		}

		p1.init(h2, h1);
		p2.init(h1, h2);
	}
};

