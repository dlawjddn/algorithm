#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

int map[101][101], visited[101][101][256], treasure[101][101];
int sizeX=0, sizeY=0, moveX[4]={0,1,0,-1}, moveY[4]={-1,0,1,0};
struct Finder{
    int y, x, move, bomul;
    Finder(int tempY, int tempX, int tempMove, int tempBomul){
        y=tempY;
        x=tempX;
        move=tempMove;
        bomul = tempBomul;
    }
};

struct cmp{
    bool operator()(Finder a, Finder b){
        return a.move > b.move;
    }
};

bool checkBound(int y, int x){
    return y>0 && y<=sizeY && x>0 && x<=sizeX;
}

int minimumMove(int now, int next){
    if (now == next) return 0;
    else if (now < next) return next - now;
    else return next - (now - 4);
}

void findBomul(int tCnt){
    Finder start(1,1,0,0);
    priority_queue<Finder, vector<Finder>, cmp> pq;
    pq.push(start);
    visited[start.y][start.x][start.bomul] = 0;
    while(!pq.empty()){
        Finder now = pq.top(); 
        pq.pop();
        if (now.y == sizeY && now.x == sizeX && now.bomul == ((1<<tCnt)) - 1){
            cout<<visited[now.y][now.x][now.bomul]<<"\n";
            break;
        }
        if (visited[now.y][now.x][now.move] != now.move) continue;
        for(int d=0; d<4; d++){
            Finder next(now.y+moveY[d], now.x+moveX[d], now.move+1, now.bomul);
            if (checkBound(next.y, next.x)){
                if (treasure[now.y][now.x]){
                    next.bomul |= 1<<(treasure[now.y][now.x] - 1);
                }
                int minMove = minimumMove((map[now.y][now.x]+visited[now.y][now.x][now.bomul])%4,d);
                next.move = 1 + visited[now.y][now.x][now.bomul] + minMove;
                if(visited[next.y][next.x][next.bomul] > next.move){
                    pq.push(next);
                    visited[next.y][next.x][next.bomul] = next.move;
                }
            }
        }
    }

}

int main(){
    int tCnt=0, tY=0, tX=0;
    while(cin>>sizeY>>sizeX){
        if (sizeY == 0 && sizeX == 0) break;
        memset(visited,0x3f,sizeof(visited));
        memset(map, false, sizeof(map));
        memset(treasure, false, sizeof(treasure));
        for(int y=1; y<=sizeY; y++){
            string s;
            cin>>s;
            for(int x=1; x<=sizeX; x++){
                if (s[x-1] == 'N') map[y][x] = 0;
                else if (s[x-1] == 'W') map[y][x] = 1;
                else if (s[x-1] == 'S') map[y][x] = 2;
                else map[y][x] = 3;
            }
        }
        cin >> tCnt;
        for(int t = 1; t<=tCnt;  t++){
            cin >> tY >> tX;
            treasure[tY][tX] = t;
        }
        findBomul(tCnt);
    }
}
