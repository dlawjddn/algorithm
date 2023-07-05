#include <iostream>
#include <regex>
using namespace std;

int main() {
	string s;
	cin >> s;
	cout << (regex_match(s, regex("(100+1+|01)+")) ? "SUBMARINE": "NOISE") << endl;
}
