#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Info {
    int y, x;
    vector<pair<int, int> > path;
};
int sizeY, sizeX, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<string> maps;
vector<string> result;
vector<pair<int, int> > points;

void print_result(){
    for(int y=0; y<sizeY; y++) {
        for(int x=0; x<sizeX; x++) {
            cout<<result[y][x];
        }
        cout<<"\n";
    }
}

Info make_info(int y, int x, vector<pair<int, int> > path) {
    Info info;
    info.y = y;
    info.x = x;
    info.path = path;
    return info;
}

vector<pair<int, int> > next_path(vector<pair<int, int> > path, int y, int x) {
    path.push_back(make_pair(y, x));
    return path;
}

bool check_outside(int y, int x) {
    return y < 0 || y >= sizeY || x < 0 || x >= sizeX;
}

vector<pair<int, int> > bfs() {
    queue<Info> q;
    vector<vector<bool> > visited(sizeY, vector<bool>(sizeX, false));
    q.push(make_info(points[0].first, points[0].second, next_path(vector<pair<int, int> >(), points[0].first, points[0].second)));
    visited[points[0].first][points[0].second] = true;
    while(!q.empty()) {
        auto[y, x, path] = q.front(); q.pop();
        if (y == points[1].first && x == points[1].second) {
            return path;
        }
        for(int d=0; d<4; d++) {
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            if (check_outside(ny, nx) || maps[ny][nx] == '+' || visited[ny][nx]) continue;
            q.push(make_info(ny, nx, next_path(path, ny, nx)));
            visited[ny][nx] = true;
        }
    }

}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>sizeY>>sizeX;
    maps.resize(sizeY);
    result.resize(sizeY);
    for(int y=0; y<sizeY; y++) {
        cin>>maps[y];
        result[y] = maps[y];
        for(int x=0; x<sizeX; x++) {
            if (maps[y][x] == '.' && ((x == 0 || x == sizeX - 1) || (y == 0 || y == sizeY - 1))) {
                points.push_back(make_pair(y, x));
                continue;
            }
            if (maps[y][x] == '.') result[y][x] = '@';
        }
    }
    // for(auto point : points) {
    //     cout<<point.first<<" "<<point.second<<"\n";
    // }
    // print_result();
    // cout<<"\n";
    vector<pair<int, int> > path = bfs();
    for(auto p : path) {
        result[p.first][p.second] = '.';
    }
    print_result();
}