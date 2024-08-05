#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

vector<int> split(string origin, char delimeter) {
    vector<int> result;
    string token;
    istringstream tokenStream(origin);
    while(getline(tokenStream, token, delimeter)) {
        result.push_back(stoi(token));
    }
    return result;
}

string solution(string s) {
    vector<int> numbers = split(s, ' ');
    sort(numbers.begin(), numbers.end());
    return to_string(numbers.front()) + " " + to_string(numbers.back());
}