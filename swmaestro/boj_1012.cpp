#include <iostream>
#include <cstring>
using namespace std;

int map[50][50];
int visited[50][50], moveX[4]={1,0,-1,0}, moveY[4]={0,1,0,-1}, test=0, sizeX=0, sizeY=0, cnt=0;
void printMap(int sizeY, int sizeX){
    cout<<"\n";
    for(int y=0; y<sizeY; y++){
        for(int x=0; x<sizeX; x++){
            cout<<map[y][x]<<" ";
        }
        cout<<"\n";
    }
}
bool checkBound(int y, int x, int sizeY, int sizeX){
    return y>=0 && y<sizeY && x>=0 && x<sizeX;
}
void dfs(int y, int x, int sizeY, int sizeX){
    visited[y][x] = 1;
    for(int d=0; d<4; d++){
        int ny = y + moveY[d];
        int nx = x + moveX[d];
        if (checkBound(ny, nx, sizeY, sizeX) && map[ny][nx] == 1 && visited[ny][nx] == 0){
            dfs(ny, nx, sizeY, sizeX);
        }
    }
}
int findAns(int sizeY, int sizeX){
    int sol = 0;
    for(int y=0; y<sizeY; y++){
        for(int x=0; x<sizeX; x++){
            if (map[y][x] == 1 && visited[y][x] == 0){
                dfs(y,x, sizeY, sizeX);
                sol++;
            }
        }
    }
    return sol;
}
int main(){
    cin>>test;
    for(int i=0; i<test; i++){
        cin>>sizeX>>sizeY>>cnt;
        for(int j=0; j<cnt; j++){
            int tempX = 0, tempY = 0;
            cin>>tempX>>tempY;
            map[tempY][tempX] = 1;
        }
        cout<<findAns(sizeY, sizeX)<<"\n";
        memset(map, 0, sizeof(map));
        memset(visited, 0, sizeof(visited));
    }
}