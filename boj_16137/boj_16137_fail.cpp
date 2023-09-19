#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int sizeSQ=0, bridge=0;
int map[10][10], visited[10][10];
int moveX[4]={1,0,-1,0}, moveY[4]={0,1,0,-1};

bool checkWait[10][10];

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
bool canBuildBridge(int y, int x){
    int check = 0;
    if (checkBound(y-1, x) && map[y-1][x] == 0) check++;
    if (checkBound(y+1, x) && map[y+1][x] == 0) check++;
    if (checkBound(y, x-1) && map[y][x-1] == 0) check++;
    if (checkBound(y, x+1) && map[y][x+1] == 0) check++;
    if (check >= 2) return false;
    return true;
}

int go_to_jiknyeo(int startY, int startX){
    queue<pair<int, int> > q;
    q.push(make_pair(startY, startX));
    visited[startY][startX] = 1;
    while(!q.empty()){
        int y = q.front().first;
        int x = q.front().second; q.pop();
        cout<<"y: "<<y<<" x: "<<x<<"\n";
        if (y == sizeSQ-1 && x == sizeSQ - 1){
            return visited[y][x] - 1;
        }
        for(int d=0; d<4; d++){
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            if (checkBound(ny, nx) && !visited[ny][nx]){
                if (map[ny][nx] == 1){
                    q.push(make_pair(ny, nx));
                    visited[ny][nx] = visited[y][x] + 1;
                }
                else if (map[ny][nx] == 0){ // 절벽인 경우
                    if (checkBridgeTwice(y,x,ny,nx) && canBuildBridge(ny, nx) &&visited[y][x] % bridge == 0){ //  한번에 통과 되는 경우
                        q.push(make_pair(ny, nx));
                        visited[ny][nx] = visited[y][x] + 1;
                    }
                    // else{ // 한번에 통과 안 되는 경우
                    //     if (!checkWait[y][x]){
                    //         q.push(make_pair(y, x));
                    //         visited[y][x] = bridge * ((visited[y][x] / bridge) + 1);
                    //         checkWait[y][x] = true;
                    //     }
                    // }
                }
                else{ // 2 이상의 수
                    if (checkBridgeTwice(y,x,ny,nx) && visited[y][x] % bridge == 0){ // 한번에 통과되는 경우
                        q.push(make_pair(ny, nx));
                        visited[ny][nx] = visited[y][x] + 1;
                    }
                    // else{ // 한번에 통과 안 되는 경우
                    //     if (!checkWait[y][x]){
                    //         q.push(make_pair(y, x));
                    //         visited[y][x] = bridge * ((visited[y][x] / bridge) + 1);
                    //         checkWait[y][x] = true;
                    //     }
                    // }
                }
            }
        }
    }
    return 0;
}
int main(){
    cin>>sizeSQ>>bridge;
    for(int i=0; i<sizeSQ; i++){
        for(int j=0; j<sizeSQ; j++){
            cin>>map[i][j];
        }
    }
    cout<<go_to_jiknyeo(0,0)<<"\n";
    for(int i=0; i<sizeSQ; i++){
        for(int j=0; j<sizeSQ; j++){
            cout<<visited[i][j]<<" ";
        }
        cout<<"\n";
    }
}