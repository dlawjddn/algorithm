#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int sizeY, sizeX, answer = 0, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<vector<int> > maps;
vector<vector<bool> > visited;
vector<pair<int, int> > zeros;
vector<pair<int, int> > viruses;

bool check_outside(int y, int x) {
    return y < 0 || y >= sizeY || x < 0 || x >= sizeX;
}

int spread_virus() {
    int result = 0;
    visited = vector<vector<bool> >(sizeY, vector<bool>(sizeX, false));
    vector<vector<int> > temp_maps = maps;
    queue<pair<int, int> > q;
    for(int i=0; i<viruses.size(); i++) {
        auto[y, x] = viruses[i];
        q.push({y, x});
        visited[y][x] = true;
    }
    while(!q.empty()) {
        auto[y, x] = q.front(); q.pop();
        for(int d=0; d<4; d++) {
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            if (check_outside(ny, nx) || visited[ny][nx] || temp_maps[ny][nx] != 0) continue;
            q.push({ny, nx});
            temp_maps[ny][nx] = 2;
            visited[ny][nx] = true;
        }
    }
    for(int y=0; y<sizeY; y++) {
        for(int x=0; x<sizeX; x++) {
            if (temp_maps[y][x] == 0) result++;
        }
    }
    return result;
}

void change_state(vector<int>& chosen) {
    for(int i=0; i<chosen.size(); i++) {
        auto[y, x] = zeros[chosen[i]];
        maps[y][x] = (maps[y][x] == 1 ? 0 : 1);
    }
}

void combination(int idx, int depth, vector<int> &chosen, vector<bool>& check) {
    if (depth == 3) {
        // 빈칸 -> 벽 되는 3칸 변경
        change_state(chosen);
        // 바이러스 퍼트리기
        answer = max(answer, spread_virus());
        // 원복하기
        change_state(chosen);

        // for(int i=0; i<chosen.size(); i++) {
        //     cout<<chosen[i]<<" ";
        // }
        // cout<<"\n";
        return ;
    }
    for(int i=idx; i<zeros.size(); i++) {
        if (check[i]) continue;
        check[i] = true;
        chosen.push_back(i);
        combination(i, depth + 1, chosen, check);
        chosen.pop_back();
        check[i] = false;
    }
}

int main() {
    cin>>sizeY>>sizeX;
    maps.resize(sizeY, vector<int>(sizeX));
    for(int y=0; y<sizeY; y++) {
        for(int x=0; x<sizeX; x++) {
            cin>>maps[y][x];
            if (maps[y][x] == 0) zeros.push_back({y, x});
            else if (maps[y][x] == 2) viruses.push_back({y, x});
        }
    }
    vector<int> chosen;
    vector<bool> check(zeros.size(), false);
    combination(0, 0, chosen, check);
    cout<<answer;
}