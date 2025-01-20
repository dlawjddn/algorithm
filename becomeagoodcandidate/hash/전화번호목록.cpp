#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

unordered_set<string> checker;

bool solution(vector<string> phone_book) {
    sort(phone_book.begin(), phone_book.end());
    for(int i=0; i<phone_book.size(); i++) {
        for(int j=0; j<phone_book[i].size(); j++) {
            string prefix = phone_book[i].substr(0, j+1);
            if (checker.find(prefix) != checker.end()) return false;
        }
        checker.insert(phone_book[i]);
    }
    return true;
}