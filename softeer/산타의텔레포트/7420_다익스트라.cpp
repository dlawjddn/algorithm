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
int moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0}, sizeY=0, sizeX=0;
pair<int, int> gift_pos;

void print_telpo(){
    for(int i=0; i<telpo.size(); i++){
        if (telpo[i].size() == 0) continue;
        cout<<"i: "<<i<<" ";
        for(int j=0; j<telpo[i].size(); j++){
            cout<<telpo[i][j].first<<" "<<telpo[i][j].second<<"  ";
        }
        cout<<"\n";
    }
}

void print_visited(vector<vector<int> > visited){
    for(int y=1; y<=sizeY; y++){
        for(int x=1; x<=sizeX; x++){
            cout<<visited[y][x]<<" ";
        }
        cout<<"\n";
    }
}

bool check_outside(int y, int x){
    return y < 1 || y > sizeY || x < 1 || x > sizeX;
}

Santa make_santa(int y, int x, int cost){
    Santa santa;
    santa.y = y;
    santa.x = x;
    santa.cost = cost;
    return santa;
}

int find_gift(int sy, int sx){
    vector<vector<int> >visited(501, vector<int>(501, 987654321));
    priority_queue<Santa> pq;
    pq.push(make_santa(sy, sx, 0));
    visited[sy][sx] = 0;
    while(!pq.empty()){
        Santa now = pq.top(); pq.pop();
        for(int d=0; d<4; d++){
            int ny = now.y + moveY[d];
            int nx = now.x + moveX[d];
            // 범위 밖 예외처리, 방문 예외처리, 벽 예외처리
            if (check_outside(ny, nx) || visited[ny][nx] <= now.cost || map[ny][nx] == 0) continue;
            // 선물인 경우
            if (map[ny][nx] == -2){
                print_visited(visited);
                return now.cost;
            }
            // 빈칸이거나 텔레포트가 가능한 지역인 경우 -> 갈 수 있는 곳
            else if (map[ny][nx] == 0 || map[ny][nx] >= 10){
                pq.push(make_santa(ny, nx, now.cost));
                visited[ny][nx] = now.cost;
                // 텔레포트가 가능한 경우
                if (map[ny][nx] >= 10){
                    for(int i=0; i<telpo[map[ny][nx]].size(); i++){
                        int ty = telpo[map[ny][nx]][i].first;
                        int tx = telpo[map[ny][nx]][i].second;
                        // 이미 방문을 한 경우 -> pq 이기 때문에 걸어서 갈 수 있는 곳 or 이전에 텔포로 이동한 곳 제외
                        if (visited[ty][tx] <= now.cost + 1) continue;
                        pq.push(make_santa(ty, tx, now.cost+1));
                        visited[ty][tx] = now.cost + 1;
                    }
                }
            }
        }
    }
    print_visited(visited);
    return -1;
}

int go_dest(int y, int x, int cost){
    // 선물을 못 찾은 경우
    if (cost == -1)
        return -1;
    vector<vector<int> > visited(501, vector<int>(501, 987654321));
    priority_queue<Santa> pq;
    pq.push(make_santa(y, x, cost));
    visited[y][x] = cost;
    while(!pq.empty()){
        Santa now = pq.top(); pq.pop();
        for(int d=0; d<4; d++){
            int ny = now.y + moveY[d];
            int nx = now.x + moveX[d];
            if (check_outside(ny, nx) || visited[ny][nx] <= now.cost || map[ny][nx] == -1) continue;
            // 우하단인 경우 -> 도착지점
            if (ny == sizeY && nx == sizeX){
                return now.cost;
            }
            // 빈칸이거나 텔레포트가 가능한 지역인 경우 -> 갈 수 있는 곳
            else if (map[ny][nx] == 0 || map[ny][nx] >= 10){
                pq.push(make_santa(ny, nx, now.cost));
                visited[ny][nx] = now.cost;
                // 텔레포트가 가능한 경우
                if (map[ny][nx] >= 10){
                    for(int i=0; i<telpo[map[ny][nx]].size(); i++){
                        int ty = telpo[map[ny][nx]][i].first;
                        int tx = telpo[map[ny][nx]][i].second;
                        // 이미 방문을 한 경우 -> pq 이기 때문에 걸어서 갈 수 있는 곳 or 이전에 텔포로 이동한 곳 제외
                        if (visited[ty][tx] <= now.cost + 1) continue;
                        pq.push(make_santa(ty, tx, now.cost+1));
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
            int num = stoi(s);
            map[y][x] = num;
            if (map[y][x] == -2)
                gift_pos = make_pair(y, x);
            else if (map[y][x] >= 10){
                telpo[map[y][x]].push_back(make_pair(y, x));
            }
        }
    }
    cout<<go_dest(gift_pos.first, gift_pos.second, find_gift(1, 1));
}