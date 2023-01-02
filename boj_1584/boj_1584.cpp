#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
struct Info{
    int y, x, cost;
    bool operator<(const Info& k)const{
    return cost > k.cost;
  }
};
int map[501][501], visited[501][501], moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0}, dangerous=0, death=0;
bool checkBound(int y, int x){
    if (y>=0 && y<=500 && x>=0 && x<=500) return true;
    return false;
}
void Dijkstra(int sy, int sx, int scost){
    priority_queue<Info> pq;
    pq.push({sy, sx, scost});
    visited[sy][sx]=scost;
    while(!pq.empty()){
        int y=pq.top().y;
        int x=pq.top().x;
        int cost=pq.top().cost;
        pq.pop();
        if (cost > visited[y][x]) continue;
        for(int d=0; d<4; d++){
            int ny=y+moveY[d];
            int nx=x+moveX[d];
            int ncost=cost;
            if (checkBound(ny, nx) && map[ny][nx]!=2){
                if (map[ny][nx]) ncost++;
                if (ncost<visited[ny][nx]){
                    pq.push({ny, nx, ncost});
                    visited[ny][nx]=ncost;
                }
            }
        }
    }
}
int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>dangerous;
    for(int i=0; i<dangerous; i++){
        int x1, y1, x2, y2;
        cin>>x1>>y1>>x2>>y2;
        int startY=min(y1, y2), endY=max(y1, y2);
        int startX=min(x1, x2), endX=max(x1, x2);
        for(int y=startY; y<=endY; y++){
            for(int x=startX; x<=endX; x++){
                map[y][x]=1;
            }
        }
    }
    cin>>death;
    for(int i=0; i<death; i++){
        int x1, y1, x2, y2;
        cin>>x1>>y1>>x2>>y2;
        int startY=min(y1, y2), endY=max(y1, y2);
        int startX=min(x1, x2), endX=max(x1, x2);
        for(int y=startY; y<=endY; y++){
            for(int x=startX; x<=endX; x++){
                map[y][x]=2;
            }
        }
    }
    memset(visited, 0xf, sizeof(visited));
    Dijkstra(0,0,0);
    if (visited[500][500]==252645135) cout<<"-1";
    else cout<<visited[500][500];
}