#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
bool visited[300][300];
int map[3000][300], copy_map[300][300], moveX[4]={1,0,-1,0}, moveY[4]={0,1,0,-1}, sizeY=0, sizeX=0, cnt=0, group=0;
bool checkBound(int y, int x){
    if (y>=0 && y<sizeY && x>=0 && x<sizeX) return true;
    return false;
}
void use_dfs(int y, int x){
    visited[y][x]=true;
    for(int d=0; d<4; d++){
        int ny=y+moveY[d];
        int nx=x+moveX[d];
        if (checkBound(ny, nx) && !visited[ny][nx] && map[ny][nx]>0) use_dfs(ny, nx);
    }
}
bool countingGroup(){
    group=0;
    memset(visited, 0, sizeof(bool)*300*300);
    for(int y=0; y<sizeY; y++){
        for(int x=0; x<sizeX; x++){
            if (!visited[y][x] && map[y][x]>0) {
                use_dfs(y,x);
                group++;
            }
        }
    }
    if (group==1) return true;
    else if (group>1) {
        cout<<cnt;
        return false;
    }
    else {
        cout<<0;
        return false;
    }

}
void melting(){
    copy(&map[0][0], &map[0][0]+300*300, &copy_map[0][0]);
    for(int a=0; a<sizeY; a++){
        for(int b=0; b<sizeX; b++){
            if (copy_map[a][b]>0){
                int ocean_cnt=0;
                for(int d=0; d<4; d++){
                    int ny=a+moveY[d];
                    int nx=b+moveX[d];
                    if (checkBound(ny, nx) && copy_map[ny][nx]==0) ocean_cnt++;
                }
                map[a][b]=copy_map[a][b]-ocean_cnt;
                if (map[a][b]<0) map[a][b]=0;
            }
        }
    }
}
int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>sizeY>>sizeX;
    for(int i=0; i<sizeY; i++){
        for(int j=0; j<sizeX; j++){
            cin>>map[i][j];
        }
    }
    while(1){
        cnt++;
        melting();
        if (!countingGroup()) break;
    }
}