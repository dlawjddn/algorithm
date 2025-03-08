#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

int main() {
    string origin, dest; cin>>origin>>dest;

    int idx = 0;
    int answer = 0;
    while(idx < dest.size()) {
        for(int len = dest.size() - idx; len > 0; len--) {
            if (origin.find(dest.substr(idx, len)) != string::npos) {
                idx += len;
                answer += 1;
                break;
            }
        }
    }
    cout<<answer;
}