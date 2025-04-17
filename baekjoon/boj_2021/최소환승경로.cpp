#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>

#define INF 987654321

using namespace std;

int subway_cnt, line_cnt, src, dest;
unordered_map<int, vector<int> > lines;
vector<vector<int> > subways;
vector<int> visited_subway;
vector<bool> visited_line;
queue<int> q;

int main() {
    cin>>subway_cnt>>line_cnt;
    subways.resize(subway_cnt + 1);
    visited_subway.resize(subway_cnt + 1, INF);
    visited_line.resize(line_cnt + 1, false);
    for(int i=1; i<=line_cnt; i++) {
        while(1) {
            int subway; cin>>subway;
            if (subway == -1) break;
            lines[i].push_back(subway);
            subways[subway].push_back(i);
        }
    }
    cin>>src>>dest;
    for(int i=0; i<subways[src].size(); i++) {
        int line = subways[src][i];
        visited_line[line] = true;
        for(int j=0; j<lines[line].size(); j++) {
            int subway = lines[line][j];
            if (visited_subway[subway] != INF) continue;
            q.push(subway);
            visited_subway[subway] = 0;
        }
    }

    while(!q.empty()) {
        int subway = q.front(); q.pop();
        for(int x=0; x<subways[subway].size(); x++) {
            int line = subways[subway][x];
            if (visited_line[line]) continue;
            visited_line[line] = true;
            for(int y=0; y<lines[line].size(); y++) {
                int nsubway = lines[line][y];
                if (visited_subway[nsubway] != INF) continue;
                q.push(nsubway);
                visited_subway[nsubway] = visited_subway[subway] + 1;
            }
        }
    }
    cout<<((visited_subway[dest] == INF) ? -1 : visited_subway[dest]);
}