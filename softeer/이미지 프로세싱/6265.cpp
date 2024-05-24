#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
int sizeY = 0, sizeX=0, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0}, order_cnt = 0;
vector<vector<int> > map(128, vector<int>(128, 0));

bool check_outside(int y, int x){
    return y < 0 || y >= sizeY || x < 0 || x >= sizeX;
}

void bfs(int startY, int startX, int origin, int change){
    queue<pair<int, int> > q;
    vector<vector<bool> > visited(sizeY, vector<bool>(sizeX, false));
    q.push(make_pair(startY, startX));
    map[startY][startX] = change;
    visited[startY][startX] = true;
    while(!q.empty()){
        int y = q.front().first;
        int x = q.front().second; q.pop();
        for(int d=0; d<4; d++){
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            if (check_outside(ny, nx) || visited[ny][nx] || map[ny][nx] != origin) continue;
            q.push(make_pair(ny, nx));
            visited[ny][nx] = true;
            map[ny][nx] = change;
        }
    }
}

void print_map(){
    for(int y=0; y<sizeY; y++){
        for(int x=0; x<sizeX; x++){
            cout<<map[y][x]<<" ";
        }
        cout<<"\n";
    }
}

int main(int argc, char** argv)
{
    cin>>sizeY>>sizeX;
    for(int y=0; y<sizeY; y++){
        for(int x=0; x<sizeX; x++){
            cin>>map[y][x];
        }
    }
    cin>>order_cnt;
    for(int i=0; i<order_cnt; i++){
        int startY = 0, startX = 0, number = 0;
        cin>>startY>>startX>>number;
        bfs(startY-1, startX-1, map[startY-1][startX-1], number);
    }
    print_map();
}