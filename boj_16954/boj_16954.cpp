#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

char map[8][8];
bool breakPoint[8][8][8]; // [y][x][이동 횟수] -> [1][1][1] == [1][1]에 1회 이동한 경우에 벽이 존재
int moveX[9] = {0,1,1,0,-1,-1,-1,0,1}, moveY[9]={0,0,-1,-1,-1,0,1,1,1};
struct Point{
    int x, y, move;
};
Point wall[64];
queue<Point> q;
void checkbreakPoint(int cnt){
    for(int i=0; i<cnt; i++){
        int downCnt = 0;
        int tempY = wall[i].y;
        int tempX = wall[i].x;
        while(tempY <=7){
            breakPoint[tempY++][tempX][downCnt++] = true;
        }
    }
}
bool checkBound(int y, int x){
    if (y<8 && y>=0 && x<8 && x>=0) return true;
    return false;
}
bool movingPerson(){
    queue<Point> q;
    Point start;
    start.y=7; start.x=0; start.move=0;
    q.push(start);
    while(!q.empty()){
        Point now = q.front(); q.pop();
        if (now.y==0 && now.x==7) return true;
        for(int d=0; d<9; d++){
            Point next;
            next.y = now.y+moveY[d];
            next.x = now.x+moveX[d];
            next.move = now.move+1;
            if (checkBound(next.y, next.x) && !breakPoint[next.y][next.x][next.move] && !breakPoint[next.y][next.x][next.move-1]){
                q.push(next);
            }
        }
    }
    return false;
}
int main(){
    //input
    int cnt = 0; // wall count
    for(int i=0; i<8; i++){
        string s;
        cin>>s;
        for(int j=0; j<8; j++){
            map[i][j] = s[j];
            if (map[i][j] == '#'){
                Point temp;
                temp.y = i;
                temp.x = j;
                wall[cnt++] = temp;
            }
        }
    }
    checkbreakPoint(cnt);
    cout<<movingPerson();
}