#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

bool check(const string& origin, const string& cmp) {
    if (origin.size() < cmp.size()) return false;
    return (origin.substr(0, cmp.size()) == cmp) ? true : false;
}

int main() {
    int dest_cnt, src_cnt; cin>>dest_cnt>>src_cnt;
    int answer = 0;
    set<string> dest;
    for(int i=0; i<dest_cnt; i++) {
        string str; cin>>str;
        dest.insert(str);
    }

    for(int i=0; i<src_cnt; i++) {
        string str; cin>>str;
        auto it = dest.lower_bound(str);
        if (it != dest.end() && check(*it, str)) answer++;
    }
    cout<<answer;
}