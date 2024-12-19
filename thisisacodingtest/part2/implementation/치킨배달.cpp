#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

#define INF 987654321

using namespace std;

int sq_size, choose_cnt, chicken_cnt, home_cnt, answer = INF;
vector<vector<int> > maps;
vector<pair<int, int> > home;
vector<pair<int, int> > chicken;
vector<vector<int> > cost;
vector<bool> visited;

void solve(vector<int>& chosen) {
    vector<int> result(home_cnt, INF);

    for(int i=0; i<chosen.size(); i++) {
        int c = chosen[i];
        for(int h=0; h<result.size(); h++) {
            result[h] = min(result[h], cost[h][c]);
        }
    }

    answer = min(answer, accumulate(result.begin(), result.end(), 0));
}

void combination(int idx, int depth, vector<int> chosen) {
    if (depth == choose_cnt) {
        solve(chosen);
        return ;
    }
    for(int i=idx; i<chicken_cnt; i++) {
        if (visited[i]) continue;
        visited[i] = true;
        chosen.push_back(i);
        combination(i, depth + 1, chosen);
        chosen.pop_back();
        visited[i] = false;
    }
}

int main() {
    cin>>sq_size>>choose_cnt;
    maps.resize(sq_size, vector<int>(sq_size, 0));
    for(int y=0; y<sq_size; y++) {
        for(int x=0; x<sq_size; x++) {
            cin>>maps[y][x];
            if (maps[y][x] == 1) home.push_back({y, x});
            else if (maps[y][x] == 2) chicken.push_back({y, x});
        }
    }
    home_cnt = home.size();
    chicken_cnt = chicken.size();
    visited.resize(chicken_cnt, false);
    cost.resize(home.size(), vector<int>(chicken.size()));
    for(int h=0; h<home.size(); h++) {
        for(int c=0; c<chicken.size(); c++) {
            auto[hy, hx] = home[h];
            auto[cy, cx] = chicken[c];
            cost[h][c] = abs(hy - cy) + abs(hx - cx);
        }
    }
    combination(0, 0, vector<int>{});
    cout<<answer;
}