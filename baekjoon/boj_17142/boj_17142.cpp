/**
 * @file boj_17142.cpp
 * @brief 백준 gold3 연구소 3
 * @version 0.1
 * @date 2024-07-09
 * 
 * @copyright Copyright (c) 2024
 * 
 * 데이터 추가로 오답이 된 문제인데.. 원트컷~!! 성장했구나!
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int sq_size, choose, empty_cnt = 0, answer = 987654321, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<vector<int> > maps;
vector<pair<int, int> > viruses;
vector<bool> choose_visited;

bool check_outside(int y, int x) {
    return y < 0 || y >= sq_size || x < 0 || x >= sq_size;
}

void spread_virus(vector<int> activate) {
    queue<pair<int, int> > q;
    vector<vector<int> > visited(sq_size, vector<int>(sq_size, 0));
    for(auto idx :activate) {
        q.push(viruses[idx]);
        visited[viruses[idx].first][viruses[idx].second] = 1;
    }
    int cnt = 0, cost = 0;
    while(!q.empty()) {
        auto[y, x] = q.front(); q.pop();
        if (maps[y][x] == 0) {
            cnt++;
            cost = max(cost, visited[y][x] - 1);
        }
        for(int d=0; d<4; d++) {
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            if (check_outside(ny, nx) || visited[ny][nx] != 0 || maps[ny][nx] == 1) continue;
            q.push(make_pair(ny, nx));
            visited[ny][nx] = visited[y][x] + 1;
        }
    }
    if (cnt == empty_cnt) {
        answer = min(answer, cost);
    }
}

vector<int> add_vector(vector<int> chosen, int idx) {
    chosen.push_back(idx);
    return chosen;
}

void choose_virus(int idx, int cnt, vector<int> chosen) {
    if (cnt == choose) {
        //for(auto c : chosen) cout<<c<<" ";
        //cout<<"\n";
        spread_virus(chosen);
    }
    for(int i=idx; i<viruses.size(); i++) {
        if (choose_visited[i]) continue;
        choose_visited[i] = true;
        choose_virus(i, cnt + 1, add_vector(chosen, i));
        choose_visited[i] = false;
    }
}

int main(){
    cin>>sq_size>>choose;
    maps.resize(sq_size, vector<int>(sq_size, 0));
    for(int y=0; y<sq_size; y++) {
        for(int x=0; x<sq_size; x++) {
            cin>>maps[y][x];
            if (maps[y][x] == 2) viruses.push_back(make_pair(y, x));
            else if (maps[y][x] == 0) empty_cnt++;
        }
    }
    choose_visited.resize(viruses.size(), false);
    choose_virus(0, 0, vector<int>());
    (answer == 987654321) ? cout<<-1 : cout<<answer;
}