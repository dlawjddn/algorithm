#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;

struct Point{
    int y, x, trash, near;
    Point (int tempY, int tempX, int tempTrash, int tempNear){
        y = tempY;
        x = tempX;
        trash = tempTrash;
        near = tempNear;
    }
};
struct cmp{
    bool operator()(Point a, Point b){
        return a.trash > b.trash;
    }
};
int sizeY=0, sizeX=0, minTrash = 987654321, minNear=987654321, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
int map[50][50], visited[50][50];

bool checkBound(int y, int x){
    return y>=0 && y<sizeY && x>=0 && x<sizeX;
}

void findPath(int startY, int startX){
    for(int y=0; y<sizeY; y++){ // 데이크스트라 사용을 위한 이차원 배열 초기화
        for(int x=0; x<sizeX; x++){
            visited[y][x] = 987654321;
        }
    }
    priority_queue<Point, vector<Point>, cmp> pq;
    Point start(startY, startX, 0, 0);
    pq.push(start);
    visited[startY][startX] = 0;
    while(!pq.empty()){
        Point now = pq.top(); pq.pop();
        if (visited[now.y][now.x] != now.trash * 2500 + now.near) continue;
        for(int d=0; d<4; d++){
            Point next(now.y+moveY[d], now.x+moveX[d], now.trash, now.near);
            if (!checkBound(next.y, next.x)) continue;
            if (map[next.y][next.x] == 2) next.trash++;
            else if (map[next.y][next.x] == 1) next.near++;
            if (visited[next.y][next.x] > (next.trash*2500 + next.near)){
                pq.push(next);
                visited[next.y][next.x] = next.trash*2500 + next.near;
            }
        }
    }
}

int main(){
    cin>>sizeY>>sizeX;
    int startY=0, startX=0, endY=0, endX=0;
    for(int y=0; y<sizeY; y++){
        string s;
        cin>>s;
        for(int x=0; x<sizeX; x++){
            if (map[y][x] != 0 && s[x] == '.') continue; // 이전의 trash로 trash 주변이라는 것을 이미 입력한 상황
            
            if (s[x] == '.') map[y][x] = 0;
            else if (s[x] == 'S'){
                map[y][x] = 0;
                startY = y;
                startX = x;
            }
            else if (s[x] == 'g'){
                map[y][x] = 2;
                for(int d=0; d<4; d++){
                    if (!checkBound(y + moveY[d], x + moveX[d]) || map[y + moveY[d]][x + moveX[d]] != 0) continue;
                    map[y + moveY[d]][x + moveX[d]] = 1;
                }
            }
            else {
                map[y][x] = -1;
                endY=y;
                endX=x;
            }
        }
    }
    // for(int i=0; i<sizeY; i++){
    //     for(int j=0; j<sizeX; j++){
    //         cout<<map[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }
    // cout<<"\n";
    findPath(startY, startX);
    cout<<visited[endY][endX] / 2500<<" "<<visited[endY][endX] % 2500;
}