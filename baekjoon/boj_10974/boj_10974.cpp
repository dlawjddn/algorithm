#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int num=0;
	vector<int> v;
	cin>>num;
	for (int i = 0; i < num; i++) {
		v.push_back(i+1);
	}
	do {
		for (int i = 0; i < num; i++) {
			cout << v[i] << " ";
		}

		cout << '\n';

	} while (next_permutation(v.begin(), v.end()));
}

