#include <iostream>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;

struct Point{
    int y, x, move;
    Point(int tempY, int tempX, int tempMove){
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
int sizeY=0, sizeX=0, maxHeight=0, maxTime=0, ans=-1;
int map[26][26], goBack[26][26], moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};

bool checkBound(int y, int x){
    return y>=0 && y<sizeY && x>=0 && x<sizeX;
}

void dijkstra(int startY, int startX, bool isClimbed){
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
        Point now = pq.top(); pq.pop();
        if (dist[now.y][now.x] != now.move) continue; //  다익스트라의 최솟값 보장을 위한 조건문
        if (!isClimbed && now.y == 0 && now.x == 0){ // 어떤 지점에서 0,0으로 돌아오는 경우에 필요한 시간 -> 산에서 호텔로 돌아오는 시간
            goBack[start.y][start.x] = now.move;
            return ;
        }
        if (isClimbed && now.move + goBack[now.y][now.x] > maxTime) continue; // 제한된 시간을 초과하는 경우
        if (isClimbed && ans < map[now.y][now.x]) ans = map[now.y][now.x]; // 최대 높이 갱신
        for(int d=0; d<4; d++){
            Point next(now.y+moveY[d], now.x+moveX[d], now.move);
            if (checkBound(next.y, next.x) && abs(map[next.y][next.x] - map[now.y][now.x]) <= maxHeight) {
                if (map[next.y][next.x] > map[now.y][now.x]){ // 큰 수로 가는 경우
                    next.move += pow((map[next.y][next.x] - map[now.y][now.x]), 2);
                }
                else next.move += 1; // 같거나 작은 수
                if (dist[next.y][next.x] > next.move && next.move <= maxTime){ // 최소값을 보장하는 조건문, 제한된 시간안에 갈 수 있는 부분만 파악
                    pq.push(next);
                    dist[next.y][next.x] = next.move;
                }
            }
           
        }

    }

}

int main(){
    cin>>sizeY>>sizeX>>maxHeight>>maxTime;
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