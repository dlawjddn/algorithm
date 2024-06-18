#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

struct Point{
    int y, x, use;
};
int sizeSQ=0, bridge=0;
int map[10][10], visited[10][10][2];
int moveX[4]={1,0,-1,0}, moveY[4]={0,1,0,-1};

bool checkBound(int y, int x){
    return y>=0 && y<sizeSQ && x>=0 && x<sizeSQ;
}

bool checkBridgeTwice(int y, int x, int ny, int nx){
    if (map[y][x] == 0 || map[y][x] >= 2) {// 현재 위치하는 발판이 절벽이나 오작교인 경우
        if (map[ny][nx] == 0 || map[ny][nx] >= 2) //  다음 발판이 절벽이나 오작교인 경우
            return false;
    }
    return true;
}

bool checkBuildBridge(int y, int x){
    int check = 0;
    if (checkBound(y-1, x) && map[y-1][x] == 0) check++;
    if (checkBound(y+1, x) && map[y+1][x] == 0) check++;
    if (checkBound(y, x-1) && map[y][x-1] == 0) check++;
    if (checkBound(y, x+1) && map[y][x+1] == 0) check++;
    if (check >= 2) return false;
    return true;
}

void go_to_jiknyeo(){
    queue<Point> q;
    Point start; start.y=0; start.x=0; start.use=0;
    q.push(start);
    visited[start.y][start.x][start.use] = 1;
    while(!q.empty()){
        Point now = q.front();
        if (now.y == sizeSQ-1 && now.x == sizeSQ-1) return;
        q.pop();
        bool flag = false;
        for(int d = 0; d<4; d++){
            Point next;
            next.y = now.y + moveY[d];
            next.x = now.x + moveX[d];
            next.use = now.use;
            if (checkBound(next.y, next.x) && !visited[next.y][next.x][next.use]){
                if (map[next.y][next.x] == 1){
                    q.push(next);
                    visited[next.y][next.x][next.use] = visited[now.y][now.x][now.use] + 1;
                }
                else if(map[next.y][next.x] >= 2){
                    if (checkBridgeTwice(now.y, now.x, next.y, next.x)){
                        if (visited[now.y][now.x][next.use] % map[next.y][next.x] == 0){
                            q.push(next);
                            visited[next.y][next.x][next.use] = visited[now.y][now.x][now.use] + 1;
                        }
                        else flag = true;
                    }
                }
                else{ // 0인 경우에
                    if (checkBridgeTwice(now.y, now.x, next.y, next.x) && checkBuildBridge(next.y, next.x) && next.use == 0){
                        if (visited[now.y][now.x][next.use] % bridge == 0){
                            next.use = 1;
                            q.push(next);
                            visited[next.y][next.x][next.use] = visited[now.y][now.x][now.use] + 1;
                        }
                        else flag = true;
                    }
                }
            }
        }
        if (flag){
            q.push(now);
            visited[now.y][now.x][now.use]++;
        }
    
    }
}

int main(){
    cin>>sizeSQ>>bridge;
    for(int i=0; i<sizeSQ; i++){
        for(int j=0; j<sizeSQ; j++){
            cin>>map[i][j];
        }
    }
    go_to_jiknyeo();
    int temp1 = visited[sizeSQ-1][sizeSQ-1][0];
    int temp2 = visited[sizeSQ-1][sizeSQ-1][1];
    if (temp1 == 0 || temp2 == 0){
        if (temp1 == 0) cout<<temp2 -1;
        else cout<<temp1 - 1;
    }
    else cout<<min(temp1, temp2) - 1;
}
