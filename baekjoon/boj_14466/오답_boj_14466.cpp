#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int sq_size = 0, cow_cnt = 0, road_cnt = 0, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<vector<int> > maps;
vector<pair<int, int> > cows;

int custom_pos(int pos) {
    return 2 * pos - 1;
}

void print_maps(){
    for(int y=1; y<=custom_pos(sq_size); y++){
        for(int x=1; x<=custom_pos(sq_size); x++) {
            cout<<maps[y][x]<<" ";
        }
        cout<<"\n";
    }
}

void make_road(pair<int, int> from, pair<int, int> to) {
    from.first = custom_pos(from.first);
    from.second = custom_pos(from.second);

    to.first = custom_pos(to.first);
    to.second = custom_pos(to.second);

    int roady = (from.first + to.first) / 2;
    int roadx = (from.second + to.second) / 2;

    maps[roady][roadx] = -1;
}

bool check_outside(int y, int x) {
    return y < 1 || y > custom_pos(sq_size) || x < 1 || x > custom_pos(sq_size);
}

vector<vector<bool> > bfs(int sy, int sx) {
    vector<vector<bool> > visited(custom_pos(sq_size) + 1, vector<bool>(custom_pos(sq_size) + 1, false));
    queue<pair<int, int> > q;
    q.push(make_pair(sy, sx));
    visited[sy][sx] = true;
    int cnt = 0;
    while(!q.empty()) {
        int y = q.front().first;
        int x = q.front().second; q.pop();
        for(int d=0; d<4; d++) {
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            if (check_outside(ny, nx) || visited[ny][nx] || maps[ny][nx] == -1) continue;
            if (maps[ny][nx] > 0) cnt++;
            q.push(make_pair(ny, nx));
            visited[ny][nx] = true;
        }
    }
    return visited;
}

int solution() {
    int matching = 0;
    int answer = (cow_cnt * (cow_cnt - 1)) / 2;
    for(int i=0; i<cows.size() - 1; i++) {
        vector<vector<bool> > visited= bfs(cows[i].first, cows[i].second);
        for(int j=i+1; j<cows.size(); j++) {
            if (!visited[cows[j].first][cows[j].second]) matching++;
        }
    }
    return matching;
}

int main() {
    cin>>sq_size>>cow_cnt>>road_cnt;
    maps.resize(custom_pos(sq_size) + 1, vector<int>(custom_pos(sq_size) + 1, 0));
    for(int i=0; i<road_cnt; i++) {
        int from_y, from_x, to_y, to_x;
        cin>>from_y>>from_x>>to_y>>to_x;
        make_road(make_pair(from_y, from_x), make_pair(to_y, to_x));
    }
    for(int i=1; i<=cow_cnt; i++) {
        int cowy; cin>>cowy;
        int cowx; cin>>cowx;
        cows.push_back(make_pair(custom_pos(cowy), custom_pos(cowx)));
        maps[custom_pos(cowy)][custom_pos(cowx)] = i;
    }
    //print_maps();
    cout<<solution();
}
