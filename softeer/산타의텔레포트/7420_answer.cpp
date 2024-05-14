#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Santa{
    int y, x, cost;
    bool operator<(const Santa& other) const {
        return cost > other.cost;
    }
};
vector<vector<int> > map(501, vector<int>(501, 0));
vector<vector<pair<int, int> > > telpo(100001);
pair<int, int> gift_pos;
int moveY[4]={0,1,0,-1}, moveX[4] = {1,0,-1,0}, sizeY=0, sizeX=0;

void print_visited(vector<vector<int> > visited){
    for(int y=1; y<=sizeY; y++){
        for(int x=1; x<=sizeX; x++){
            cout<<visited[y][x]<<" ";
        }
        cout<<"\n";
    }
}

Santa make_santa(int y, int x, int cost){
    Santa santa;
    santa.y = y;
    santa.x = x;
    santa.cost = cost;
    return santa;
}

bool check_outside(int y, int x){
    return y < 1 || y > sizeY || x < 1 || x > sizeX;
}

int find_gift(int sy, int sx){
    vector<vector<int> > visited(501, vector<int>(501, 987654321));
    vector<bool> telpo_visited(100001, false);
    priority_queue<Santa> pq;
    pq.push(make_santa(sy, sx, 0));
    visited[sy][sx] = 0;
    while(!pq.empty()){
        Santa now = pq.top(); pq.pop();
        for(int d=0; d<4; d++){
            int ny = now.y + moveY[d];
            int nx = now.x + moveX[d];
            if (check_outside(ny, nx) || visited[ny][nx] <= now.cost || map[ny][nx] == -1) continue;
            if (map[ny][nx] == -2){
                return now.cost;
            }
            else if (map[ny][nx] == 0 || map[ny][nx] >= 10){
                pq.push(make_santa(ny, nx, now.cost));
                visited[ny][nx] = now.cost;
                if (map[ny][nx] >= 10 && !telpo_visited[map[ny][nx]]){
                    telpo_visited[map[ny][nx]] = true;
                    for(int i=0; i<telpo[map[ny][nx]].size(); i++){
                        int ty = telpo[map[ny][nx]][i].first;
                        int tx = telpo[map[ny][nx]][i].second;
                        if (visited[ty][tx] <= now.cost + 1) continue;
                        pq.push(make_santa(ty, tx, now.cost + 1));
                        visited[ty][tx] = now.cost + 1;
                    }
                }
            }
        }
    }
    return -1;
}

int go_dest(int sy, int sx, int scost){
    if (scost == -1) return -1;
    vector<vector<int> > visited(501, vector<int>(501, 987654321));
    vector<bool> telpo_visited(100001, false);
    priority_queue<Santa> pq;
    pq.push(make_santa(sy, sx, scost));
    visited[sy][sx] = scost;
    while(!pq.empty()){
        Santa now = pq.top(); pq.pop();
        for(int d=0; d<4; d++){
            int ny = now.y + moveY[d];
            int nx = now.x + moveX[d];
            if (check_outside(ny, nx) || visited[ny][nx] <= now.cost || map[ny][nx] == -1) continue;
            if (ny == sizeY && nx == sizeX){
                return now.cost;
            }
            else if (map[ny][nx] == 0 || map[ny][nx] >= 10){
                pq.push(make_santa(ny, nx, now.cost));
                visited[ny][nx] = now.cost;
                if (map[ny][nx] >= 10 && !telpo_visited[map[ny][nx]]){
                    telpo_visited[map[ny][nx]] = true;
                    for(int i=0; i<telpo[map[ny][nx]].size(); i++){
                        int ty = telpo[map[ny][nx]][i].first;
                        int tx = telpo[map[ny][nx]][i].second;
                        if (visited[ty][tx] <= now.cost + 1) continue;
                        pq.push(make_santa(ty, tx, now.cost + 1));
                        visited[ty][tx] = now.cost + 1;
                    }
                }
            }
        }
    }
    return -1;
}

int main(int argc, char** argv)
{
    cin>>sizeY>>sizeX;
    for(int y=1; y<=sizeY; y++){
        for(int x=1; x<=sizeX; x++){
            string s;
            cin>>s;
            map[y][x] = stoi(s);
            if (map[y][x] == -2)
                gift_pos = make_pair(y, x);
            else if (map[y][x] >= 10)
                telpo[map[y][x]].push_back(make_pair(y, x));
        }
    }
    cout<<go_dest(gift_pos.first, gift_pos.second, find_gift(1, 1));
}