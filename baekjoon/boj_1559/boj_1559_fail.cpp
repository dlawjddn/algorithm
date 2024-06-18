#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;

struct Point{
    int y, x, dir, move, bomul;
};
char map[100][100];
int visited[100][100][256][4];
int sizeY=0, sizeX=0;
int moveY[4]={-1,0,1,0}, moveX[4]={0,1,0,-1}, treasure[100][100];

bool checkBound(int y, int x){
    return y>=0 && y<sizeY && x>=0 && x<sizeX;
}


int startDirection(){
    if (map[0][0] == 'N') return 0;
    else if (map[0][0] == 'E') return 1;
    else if (map[0][0] == 'W') return 2;
    else return 3;
}

int checkDirection(char origin, int move){ // 내가 이동한 만큼 미로가 움직이는데 현재 내 위치에서의 문의 방향을 나타냄
    char dir[4] = {'N', 'E', 'S', 'W'};
    int edit = move % 4;
    int last_idx = 5;
    for(int d=0; d<4; d++){
        if (dir[d] == origin){
            last_idx = (d + edit) % 4;
            break;
        }
    }
    return last_idx;
}

int findBomul(int tCnt){
    queue<Point> q;
    Point start; start.y = 0; start.x = 0; start.dir = startDirection(); start.move=0; start.bomul=0;
    q.push(start);
    visited[start.y][start.x][start.bomul][start.dir] = 1;
    while(!q.empty()){
        Point now = q.front(); q.pop();
        if (now.y == sizeY-1 && now.x == sizeX-1 && now.bomul == (pow(2, tCnt+1) -2)) return now.move;
        int d = checkDirection(map[now.y][now.x], now.move);
        Point next; next.y = now.y + moveY[d]; next.x = now.x + moveX[d]; next.move = now.move + 1; next.bomul = now.bomul;
        if (checkBound(next.y, next.x) && !visited[next.y][next.x][next.bomul][next.dir]){
            if (treasure[next.y][next.x] > 0 && ((next.bomul & treasure[next.y][next.x]) != treasure[next.y][next.x])){
                next.bomul += pow(2,treasure[next.y][next.x]);
            }
            q.push(next);
            visited[next.y][next.x][next.bomul][next.dir] = visited[now.y][now.x][now.bomul][now.dir] + 1;
        }
        Point waiting; waiting.y = now.y; waiting.x = now.x; waiting.move = now.move + 1; waiting.dir = d; waiting.bomul = next.bomul;
        if (!visited[waiting.y][waiting.x][waiting.bomul][waiting.dir]){
            q.push(waiting);
            visited[waiting.y][waiting.x][waiting.bomul][waiting.dir] = visited[now.y][now.x][now.bomul][now.dir] + 1;
        }
    }
    return 0;
}

int main(){
    while(1){
        int tCnt =0, ty=0, tx=0;
        cin>>sizeY>>sizeX;
        if (sizeY == 0 && sizeX == 0) break;
        for(int y=0; y<sizeY; y++){
            string s;
            cin>>s;
            for(int x=0; x<sizeX; x++){
                map[y][x] = s[x];
            }
        }
        cin>>tCnt;
        for(int i=1; i<=tCnt; i++){
            cin>>ty>>tx;
            treasure[ty-1][tx-1] = i;
        }
        cout<<findBomul(tCnt)<<"\n";
        // for(int d=0; d<4; d++){
        //     for(int i=0; i<sizeY; i++){
        //         for(int j=0; j<sizeX; j++){
        //             cout<<visited[i][j][d]<<" ";
        //         }
        //         cout<<"\n";
        //     }
        //     cout<<"\n";
        // }
        // cout<<"\n";
        memset(map, 0, sizeof(map));
        memset(visited, 0, sizeof(visited));
        memset(treasure, 0, sizeof(treasure));
    }
}