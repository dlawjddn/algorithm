#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

char map[50][50];
int visited[50][50], moveX[4]={1,0,-1,0}, moveY[4]={0,1,0,-1}, sizeY=0, sizeX=0;
queue<pair<int, int> > q;

int bfs(){
    while(!q.empty()){
        int y = q.front().first;
        int x = q.front().second; q.pop();
        for(int d=0; d<4; d++){
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            if (ny>=0 && ny<sizeY && nx >=0 && nx<sizeX){
                if (map[ny][nx] == 'D'){ // 목적지의 경우
                    if(visited[y][x] < 0 ) {// 물이 들어온 경우
                        continue;
                    }
                    else { // 비버인 경우
                        return visited[y][x];
                    }
                }
                else { // 목적지가 아닌 경우
                    if (map[ny][nx] != 'X' && visited[ny][nx] == 0){ // 장애물이 아니고, 방문한 적이 없는 경우
                        if (visited[y][x] < 0){ // 물인 경우
                            q.push(make_pair(ny, nx));
                            visited[ny][nx] = visited[y][x] - 1;
                        } 
                        else { // 비버인 경우
                            q.push(make_pair(ny, nx));
                            visited[ny][nx] = visited[y][x] + 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}
int main(){
    int startY = 0, startX = 0;
    cin>>sizeY>>sizeX;
    for(int y=0; y<sizeY; y++){
        string s;
        cin>>s;
        for(int x=0; x<sizeX; x++){
            map[y][x] = s[x];
            if (map[y][x] == '*'){
                q.push(make_pair(y, x));
                visited[y][x] = -1;
            } else if (map[y][x] == 'S'){
                startY = y;
                startX = x;  
            }
        }
    }
    q.push(make_pair(startY, startX));
    visited[startY][startX] = 1;
    int ans = bfs();
    if (!ans) 
        cout<<"KAKTUS";
    else cout<<ans;
}