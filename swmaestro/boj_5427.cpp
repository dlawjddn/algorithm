#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

char map[1000][1000];
int visited[1000][1000];
int moveX[4]={1,0,-1,0}, moveY[4]={0,1,0,-1}, test = 0;
queue<pair<int, int> > q;
void printVisited(int sizeY, int sizeX){
    for(int y=0; y<sizeY; y++){
        for(int x=0; x<sizeX; x++){
            cout<<visited[y][x]<<" ";
        }
        cout<<"\n";
    }
}
void makeEmpty(){
    while(!q.empty()) q.pop();
}
int bfs(int sizeY, int sizeX){
    while(!q.empty()){
        int y = q.front().first;
        int x = q.front().second; q.pop();
        for(int d=0; d<4; d++){
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            if (ny>=0 && ny<sizeY && nx>=0 && nx<sizeX){ // 범위 안에 존재할 때
                if (map[ny][nx] != '#' && visited[ny][nx] == 0){
                    if (visited[y][x] < 0){ // 불인 경우
                        q.push(make_pair(ny,nx));
                        visited[ny][nx] = visited[y][x] -1;
                    } else {
                        q.push(make_pair(ny, nx));
                        visited[ny][nx] = visited[y][x] + 1;
                    }
                }
                
            } else { // 범위 바깥인 경우 -> 탈출
                if (visited[y][x] < 0) continue;
                return visited[y][x];
            }
        }
    }
    return 0;
}
int main(){
    cin>>test;
    for(int i=0; i<test; i++){
        int sizeY=0, sizeX =0, startY=0, startX=0;
        cin>>sizeX>>sizeY;
        for(int y=0; y<sizeY; y++){
            string s;
            cin>>s;
            for(int x=0; x<sizeX; x++){
                map[y][x] = s[x];
                if (map[y][x] == '*') {// 불인 경우
                    q.push(make_pair(y,x));
                    visited[y][x] = -1;
                }
                else if (map[y][x] == '@'){
                    startY = y;
                    startX = x;
                }
            }
        }
        q.push(make_pair(startY, startX));
        visited[startY][startX] = 1;
        int ans = bfs(sizeY, sizeX);
        makeEmpty();
        if (!ans) cout<<"IMPOSSIBLE\n";
        else cout<<ans<<"\n";
        memset(map, 0, sizeof(map));
        memset(visited, 0, sizeof(visited));
    }
}