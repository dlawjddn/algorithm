#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>

using namespace std;

vector<int> solution(int n, vector<string> words) {
    unordered_set<string> checker;
    string last_str = words[0];
    checker.insert(last_str);
    
    for (int i = 1; i < words.size(); i++) {
        string now_str = words[i];
        if (checker.find(now_str) != checker.end() || last_str.back() != now_str.front()) {
            int turn = (i / n) + 1; 
            int person = (i % n) + 1; 
            return {person, turn};
        }
        checker.insert(now_str);
        last_str = now_str;
    }
    return {0, 0};
}
