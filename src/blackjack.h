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
int sum(vector<int> x) {
	int s = 0, xsize = x.size();
	for (int i = 0; i < xsize; i++) {
		s += x[i];
	}
	return s;
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
	void end() {
		vector<int> h1 = p1.holdval();
		vector<int> h2 = p2.holdval();
		cout << "P1:" << sum(h1) << " P2:" << sum(h2) << endl;
		if (sum(h1) > 21 && sum(h2) > 21) {
			cout << "Draw" << endl;
		} 
		else if (sum(h1) > 21) {
			cout << "P2 Win" << endl;
		}
		else if (sum(h2) > 21) {
			cout << "P1 Win" << endl;
		}
		else if (sum(h2) > sum(h1)) {
			cout << "P2 Win" << endl;
		}
		else if (sum(h1) > sum(h2)) {
			cout << "P1 Win" << endl;
		}
		else if (sum(h1) == sum(h2) && sum(h1) > 0) {
			int h1size = h1.size(), h2size = h2.size();
			if (h1size > h2size) {
				cout << "P1 Win" << endl;
			}
			else {
				cout << "P2 Win" << endl;
			}
		}
	}
};

