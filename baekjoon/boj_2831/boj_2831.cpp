#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int cnt;
vector<int> boys;
multiset<int> boys_like_taller;
multiset<int> boys_like_shorter;
multiset<int> girls_like_taller;
multiset<int> girls_like_shorter;

int main() {
    cin>>cnt;
    for(int i=0; i<cnt; i++) {
        int boy; cin>>boy;
        boys.push_back(boy);
        if (boy < 0) {
            boys_like_shorter.insert(-1 * boy);
        } else boys_like_taller.insert(boy);
    }
    for(int i=0; i<cnt; i++) {
        int girl; cin>>girl;
        if (girl < 0) {
            girls_like_shorter.insert(-1 * girl);
        } else girls_like_taller.insert(girl);
    }

    int answer = 0;
    for (int i = 0; i < (int)boys.size(); i++) {
        int h = boys[i];
        if (h < 0) {
            auto it = girls_like_taller.lower_bound(-h);
            if (it == girls_like_taller.begin()) continue;
            girls_like_taller.erase(--it);
            answer++;
        } else {
            auto it = girls_like_shorter.upper_bound(h);
            if (it == girls_like_shorter.end()) continue;
            girls_like_shorter.erase(it);
            answer++;
        }
    }
    cout<<answer;
}