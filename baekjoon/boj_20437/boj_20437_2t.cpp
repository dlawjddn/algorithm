#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int checkmate;
string origin;
vector<vector<int> > maps;

bool init_maps() {
    maps = vector<vector<int> >(26);
    for(int i=0; i<origin.size(); i++) {
        int alpha = origin[i] - 'a';
        maps[alpha].push_back(i);
    }

    bool fail = true;
    for(int i=0; i<maps.size(); i++) {
        if (maps[i].size() >= checkmate) {
            fail = false;
            break;
        }
    }

    return !fail;
}

pair<int, int> solve() {
    bool process = init_maps();
    if (!process) return {-1, -1};

    int min_value = 1000000;
    int max_value = -1;

    for(int i=0; i<26; i++) {
        int limit_idx = maps[i].size();
        for(int j=0; j<limit_idx; j++) {
            int s = j;
            int t = j + checkmate - 1;
            if (limit_idx <= t) break;

            int len = maps[i][t] - maps[i][s] + 1;

            min_value = min(len, min_value);
            max_value = max(len, max_value);
        }
    }

    return {min_value, max_value};
}

int main() {
    int test_case; cin>>test_case;
    for(int t=0; t<test_case; t++) {
        cin>>origin>>checkmate;
        pair<int, int> result = solve();
        if (result.first == -1 && result.second == -1) {
            cout<<"-1\n";
            continue;
        }
        cout<<result.first<<" "<<result.second<<"\n";
    }
}