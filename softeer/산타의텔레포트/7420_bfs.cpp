/**
 * @file 7420.cpp
 * @brief 소프티어 산타의 텔레포트, queue 사용 버전
 * @version 0.1
 * @date 2024-05-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include<queue>

using namespace std;

struct Santa{
    int y, x, cost;
};

vector<vector<int> > map(501, vector<int>(501, 0));
vector<vector<pair<int, int> > > telpo(100001);

int moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0}, sizeY=0, sizeX=0, gift_cost = 0;
pair<int, int> gift_pos;

void print_telpo(){
    for(int i=0; i<telpo.size(); i++){
        if (telpo[i].size() == 0) continue;
        cout<<i<<": ";
        for(int j=0; j<telpo[i].size(); j++){
            cout<<telpo[i][j].first<<" "<<telpo[i][j].second<<"  ";
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

bool find_gift(int sy, int sx){
    vector<vector<int> > visited(501, vector<int>(501, 987654321));
    queue<Santa> q;
    q.push(make_santa(sy, sx, 0));
    visited[sy][sx] = 0;
    
    while(!q.empty()){
        Santa now = q.front(); q.pop();
        for(int d=0; d<4; d++){
            int ny = now.y + moveY[d];
            int nx = now.x + moveX[d];
            if (check_outside(ny, nx) || map[ny][nx] == -1 || visited[ny][nx] <= now.cost) continue;
            
            // 빈칸인 경우, 텔레포트가 가능한 경우 + 선물인 경우
            if (map[ny][nx] == 0 || map[ny][nx] >= 10 || map[ny][nx] == -2){
                // 빈칸인 경우 + 텔레포트가 가능한 경우 + 선물인 경우
                q.push(make_santa(ny, nx, now.cost));
                visited[ny][nx] = now.cost;
                // 텔레포트가 가능한 경우
                if (map[ny][nx] >= 10){
                    for(int i=0; i<telpo[map[ny][nx]].size(); i++){
                        int ty = telpo[map[ny][nx]][i].first;
                        int tx = telpo[map[ny][nx]][i].second;
                        if (visited[ty][tx] <= now.cost + 1) continue;
                        q.push(make_santa(ty, tx, now.cost+1));
                        visited[ty][tx] = now.cost+1;
                    }
                }
            }
        }
    }
    if (visited[gift_pos.first][gift_pos.second] == 987654321)
        return false;
    gift_cost = visited[gift_pos.first][gift_pos.second];
    return true;
}

int go_dest(int sy, int sx, int scost){
    vector<vector<int> > visited(501, vector<int>(501, 987654321));
    queue<Santa> q;
    q.push(make_santa(sy, sx, scost));
    visited[sy][sx] = scost;
    while(!q.empty()){
        Santa now = q.front(); q.pop();
        for(int d=0; d<4; d++){
            int ny = now.y + moveY[d];
            int nx = now.x + moveX[d];
            if (check_outside(ny, nx) || map[ny][nx] == -1 || visited[ny][nx] <= now.cost) continue;
            // 빈칸인 경우, 텔레포트가 가능한 경우 + 선물인 경우
            if (map[ny][nx] == 0 || map[ny][nx] >= 10 || map[ny][nx] == -2){
                // 빈칸인 경우 + 텔레포트가 가능한 경우 + 선물인 경우
                q.push(make_santa(ny, nx, now.cost));
                visited[ny][nx] = now.cost;
                // 텔레포트가 가능한 경우
                if (map[ny][nx] >= 10){
                    for(int i=0; i<telpo[map[ny][nx]].size(); i++){
                        int ty = telpo[map[ny][nx]][i].first;
                        int tx = telpo[map[ny][nx]][i].second;
                        if (visited[ty][tx] <= now.cost + 1) continue;
                        q.push(make_santa(ty, tx, now.cost+1));
                        visited[ty][tx] = now.cost+1;
                    }
                }
            }
        }
    }
    if (visited[sizeY][sizeX] == 987654321)
        return -1;
    else
        return visited[sizeY][sizeX];
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin>>sizeY>>sizeX;
    for(int y=1; y<=sizeY; y++){
        for(int x=1; x<=sizeX; x++){
            string s;
            cin>>s;
            map[y][x] = stoi(s);
            if (map[y][x] >= 10)
                telpo[map[y][x]].push_back(make_pair(y, x));
            else if (map[y][x] == -2)
                gift_pos = make_pair(y, x);
        }
    }
    if (!find_gift(1, 1)){
        cout<<"-1";
        return 0;
    }
    cout<<go_dest(gift_pos.first, gift_pos.second, gift_cost);
}