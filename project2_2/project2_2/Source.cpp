#include <iostream>
#include <cmath>
#include "List.h"
#include "Square.h"

using namespace std;

int main() {

	List<Square> L1, L2, L3, L4, L5;		// create 5 empty Square lists.
	
	while (L1.size() <= 20) {
		srand(time(0));
		int k = ((rand() % 100) + 1);
		Square x(k);
		L1.push_front(x);
		L2.push_back(x);
		if (!L3.contains(x)) {
			if (L3.empty()) {
				L3.insert(L3.begin(), x);
			}
			else {
				L3.insert((L3.begin() + ((rand() % L3.size()) + 1)), x);
			}
		}
		if (L3.size() == 5) {
			L4 = L3;
			L4.pop_front();
			L4.pop_back();
		}
		if (L1.size() == 5) {
			L5 = L1;
			for (List<Square>::iterator i = L5.begin(); i != L5.end(); ++i) {
				if (fmod((*i).getSide(), 2) == 1.0) {
					L5.erase(i);
				}
			}
			L5.print(L5.begin(), L5.end());
		}
	}

	cout << "L1: " << endl;		// print all lists.
	L1.print(L1.begin(), L1.end());
	cout << "L2: " << endl;
	L2.print(L2.begin(), L2.end());
	cout << "L3: " << endl;
	L3.print(L3.begin(), L3.end());
	cout << "L4: " << endl;
	L4.print(L4.begin(), L4.end());
	cout << "L5: " << endl;
	L5.print(L5.begin(), L5.end());					
		
	L1.clear();					// clear all lists.
	L2.clear();
	L3.clear();
	L4.clear();
	L5.clear();


	return 0;
}
