#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
struct Info{
    int y, x, cost;
    bool operator<(const Info& k)const{
    return cost > k.cost;
  }
};
char map[102][102];
int testCase=0, sizeY=0, sizeX=0, move_y[4]={0,1,0,-1}, move_x[4]={1,0,-1,0}, ans=987654321;
int infoDoor[102][102][3];
bool checkBound(int y, int x){
    if (y>=0 && y<=sizeY+1 && x>=0 && x<=sizeX+1) return true;
    return false;
}
void Dijkstra(int sy, int sx, int check){
    priority_queue<Info> pq;
    pq.push({sy, sx, 0});
    infoDoor[sy][sx][check]=0;
    while(!pq.empty()){
        int y = pq.top().y;
        int x = pq.top().x;
        int cost = pq.top().cost;
        pq.pop();
        if (infoDoor[y][x][check]<cost) continue;
        for(int d=0; d<4; d++){
            int ny=y+move_y[d]; 
            int nx=x+move_x[d];
            if (checkBound(ny, nx) && map[ny][nx]!='*'){
                int ncost=cost;
                if (map[ny][nx]=='#') ncost++;
                if (ncost<infoDoor[ny][nx][check]){
                    pq.push({ny, nx, ncost});
                    infoDoor[ny][nx][check]=ncost;
                }
            }
        }
    }
}
int main(){
    cin>>testCase;
    for(int i=0; i<testCase; i++){
        cin>>sizeY>>sizeX;
        bool checkFlag=false;
        int oneX=0, oneY=0, twoY=0, twoX=0;
        memset(map, '.', 102*102);
        for(int j=1; j<=sizeY; j++){
            string str;
            cin>>str;
            for(int k=1; k<=sizeX; k++){
                map[j][k]=str[k-1];
                if (map[j][k]=='$'){
                    if (!checkFlag){
                        oneY=j;
                        oneX=k;
                        checkFlag=true;
                    }
                    else{
                        twoY=j;
                        twoX=k;
                    }
                }
            }
        }
        ans=987654321;
        memset(infoDoor, 0xf, sizeof(infoDoor));
        Dijkstra(0,0,0);
        Dijkstra(oneY, oneX, 1);
        Dijkstra(twoY, twoX, 2);
        for(int a=0; a<=sizeY; a++){
            for(int b=0; b<=sizeX; b++){
                if (map[a][b]=='*') continue;
                int tempAns=infoDoor[a][b][0]+infoDoor[a][b][1]+infoDoor[a][b][2];
                if (map[a][b]=='#') tempAns-=2;
                ans=min(tempAns, ans);
            }
        }
        cout<<ans<<"\n";
    }
}