#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
#define INF 987654321
using namespace std;
char map[700][700];
int minDistance[700][700], visited[700][700], moveX[4]={1,0,-1,0}, moveY[4]={0,1,0,-1}, sizeX=0, sizeY=0;
struct Info{
    int y, x, times;
};
bool checkBound(int y, int x){
    if (y>=0 && y<sizeY && x>=0 && x<sizeX) return true;
    return false;
}
void minusOne(){
    for(int a=0; a<sizeY; a++){
        for(int b=0; b<sizeX; b++){
            visited[a][b]-=1;
        }
    }       
}
void pirateCanSee(){
    for(int y=0; y<sizeY; y++){
        int minimum=INF;
        for(int x=0; x<sizeX; x++){
            if (map[y][x]=='I'){
                minimum=INF;
                minDistance[y][x]=INF;
                continue;
            }
            minimum=min(minimum, visited[y][x]);
            minDistance[y][x]=minimum;
        }
        minimum=INF;
        for(int x=sizeX-1; x>=0; x--){
            if (map[y][x]=='I'){
                minimum=INF;
                minDistance[y][x]=INF;
                continue;
            }
            minimum=min(minimum, visited[y][x]);
            minDistance[y][x]=min(minimum, minDistance[y][x]);
        }
    }
    for(int x=0; x<sizeX; x++){
        int minimum=INF;
        for(int y=0; y<sizeY; y++){
            if (map[y][x]=='I'){
                minimum=INF;
                minDistance[y][x]=INF;
                continue;
            }
            minimum=min(minimum, visited[y][x]);
            minDistance[y][x]=min(minimum, minDistance[y][x]);
        }
        minimum=INF;
        for(int y=sizeY-1; y>=0; y--){
            if (map[y][x]=='I'){
                minimum=INF;
                minDistance[y][x]=INF;
                continue;
            }
            minimum=min(minimum, visited[y][x]);
            minDistance[y][x]=min(minimum, minDistance[y][x]);
        }
    }
}
void movingPirate(int sy, int sx){
    queue<Info> q;
    q.push({sy, sx, 1});
    visited[sy][sx]=1;
    while(!q.empty()){
        Info temp=q.front(); q.pop();
        Info next;
        for(int d=0; d<4; d++){
            next.y=temp.y+moveY[d];
            next.x=temp.x+moveX[d];
            next.times=temp.times+1;
            if (checkBound(next.y, next.x) && !visited[next.y][next.x] && map[next.y][next.x]!='I'){
                q.push(next);
                visited[next.y][next.x]=visited[temp.y][temp.x]+1;
            }
        }
    }
    minusOne();
    pirateCanSee();
}
void movingSua(int sy, int sx, int endY, int endX){
    memset(visited, 0, sizeof(visited));
    queue<Info> q;
    visited[sy][sx]=1;
    q.push({sy, sx, 0});
    while(!q.empty()){
        Info temp=q.front(); q.pop();
        for(int d=0; d<4; d++){
            Info next;
            next.y=temp.y+moveY[d];
            next.x=temp.x+moveX[d];
            next.times=temp.times+1;
            if (checkBound(next.y, next.x) && !visited[next.y][next.x] && map[next.y][next.x]!='I'){
                if (minDistance[next.y][next.x]>next.times){
                    if (next.y==endY && next.x==endX){
                        cout<<"YES";
                        return ;
                    }
                    q.push(next);
                    visited[next.y][next.x]=1;
                }
            }
        }
    }
    cout<<"NO";
    return ;
}
int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int startX=0, startY=0, pirateX=0, pirateY=0, treasureY=0, treasureX=0;
    cin>>sizeY>>sizeX;
    for(int i=0; i<sizeY; i++){
        string str;
        cin>>str;
        for(int j=0; j<sizeX; j++){
            map[i][j]=str[j];
            if (map[i][j]=='Y'){
                startY=i;
                startX=j;
            }
            else if (map[i][j]=='V'){
                pirateY=i;
                pirateX=j;
            }
            else if (map[i][j]=='T'){
                treasureY=i;
                treasureX=j;
            }
            minDistance[i][j]=INF;
        }
    }
    movingPirate(pirateY, pirateX);
    movingSua(startY, startX, treasureY, treasureX);
}