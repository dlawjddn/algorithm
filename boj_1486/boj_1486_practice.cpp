#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;

int map[27][27], goBack[27][27], moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
int sizeY=0, sizeX=0, maxMove=0, maxTime=0, ans = -1;
struct Point{
    int y, x, move;
    Point (int tempY, int tempX, int tempMove){
        y = tempY;
        x = tempX;
        move = tempMove;
    }
};
struct cmp{
    bool operator()(Point a, Point b){
        return a.move > b.move;
    }
};

bool checkBound(int y, int x){
    return y>=0 && y<sizeY && x>=0 && x<sizeX;
}

void dijkstra(int startY, int startX, bool climbed){
    int dist[26][26];
    for(int i=0; i<sizeY; i++){
        for(int j=0; j<sizeX; j++){
            dist[i][j] = 987654321;
        }
    }
    Point start(startY, startX, 0);
    priority_queue<Point, vector<Point>, cmp> pq;
    pq.push(start);
    dist[start.y][start.x] = 0;
    while(!pq.empty()){
        Point now = pq.top();
        pq.pop();
        if (dist[now.y][now.x] != now.move) continue;
        if (!climbed && now.y == 0 && now.x == 0){
            goBack[startY][startX] = now.move;
            break;
        }
        if (climbed && now.move + goBack[now.y][now.x] > maxTime) continue;
        if (climbed && map[now.y][now.x] > ans) ans = map[now.y][now.x];
        for(int d=0; d<4; d++){
            Point next(now.y + moveY[d], now.x + moveX[d], now.move);
            if (checkBound(next.y, next.x) && abs(map[next.y][next.x] - map[now.y][now.x]) <= maxMove){
                if (map[next.y][next.x] > map[now.y][now.x]) 
                    next.move += pow((map[next.y][next.x] - map[now.y][now.x]), 2);
                else next.move += 1;

                if (dist[next.y][next.x] > next.move && next.move <= maxTime){
                    pq.push(next);
                    dist[next.y][next.x] = next.move;
                }
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin>>sizeY>>sizeX>>maxMove>>maxTime;
    for(int y=0; y<sizeY; y++){
        string s;
        cin>>s;
        for(int x=0; x<sizeX; x++){
            if (s[x] >= 'A' && s[x] <= 'Z') map[y][x] = s[x] - 'A';
            else map[y][x] = s[x] - 'a' + 26;
        }
    }
    for(int y=0; y<sizeY; y++){
        for(int x=0; x<sizeX; x++){
            dijkstra(y,x, false);
        }
    }
    dijkstra(0,0,true);
    cout<<ans;

}