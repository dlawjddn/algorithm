#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define INF 987654321

using namespace std;

int rock_cnt, max_height;
vector<pair<int, int> > rocks;
vector<vector<pair<int, int> > > maps;
vector<int> visited;
struct Info {
    int x, y, cnt, idx;
    bool operator<(Info other) const {
        return cnt > other.cnt;
    }
};

void dijkstra() {
    priority_queue<Info> pq;

    for(int i=0; i<rocks.size(); i++) {
        auto[x, y] = rocks[i];
        if (abs(x) <= 2 && abs(y) <= 2) {
            pq.push({x, y, 1, i});
            visited[i] = 1;
        }
    }

    while(!pq.empty()) {
        auto[x, y, cnt, idx] = pq.top(); pq.pop();
        if (visited[idx] != cnt) continue;

        for(int ny=max(0, y-2); ny<=min(max_height, y+2); ny++) {
            for(int k=0; k<maps[ny].size(); k++) {
                auto[nx, nidx] = maps[ny][k];
                int ncnt = cnt + 1;
                if (abs(ny-y) > 2 || abs(nx-x) > 2) continue;
                if (visited[nidx] <= ncnt) continue;

                pq.push({nx, ny, ncnt, nidx});
                visited[nidx] = ncnt;
            }
        }
    }

}

int main() {
    cin>>rock_cnt>>max_height;
    visited.resize(rock_cnt, INF);
    maps.resize(max_height + 1);

    for(int i=0; i<rock_cnt; i++) {
        int x, y; cin>>x>>y;
        rocks.push_back({x, y});
        maps[y].push_back({x, i});
    }

    dijkstra();

    int ans = INF;
    for (int i = 0; i < rock_cnt; i++) {
        if (rocks[i].second == max_height) {
            ans = min(ans, visited[i]);
        }
    }
    cout << ((ans == INF) ? -1 : ans);

}