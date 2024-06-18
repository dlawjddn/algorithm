#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

char map[50][50];
int visited[50][50], check[50][50], moveX[4]={1,0,-1,0}, moveY[4]={0,1,0,-1}, sizeY, sizeX;
bool circle = false;
void printCheck(){
    for(int i=0; i<sizeY; i++){
        for(int j=0; j<sizeX; j++){
            cout<<check[i][j]<<" ";
        }
        cout<<"\n";
    }
}
void printVisited(){
    for(int i=0; i<sizeY; i++){
        for(int j=0; j<sizeX; j++){
            cout<<visited[i][j]<<" ";
        }
        cout<<"\n";
    }
}
void dfs(char mark, int group, int cnt, int y, int x){
    if (circle) return ;
    visited[y][x] = group;
    check[y][x] = cnt + 1;
    for(int d=0; d<4; d++){
        int ny = y + moveY[d];
        int nx = x + moveX[d];
        if (ny >=0 && ny<sizeY && nx >=0 && nx<sizeX){
            // 같은 모양의 블록인 경우
            if (map[ny][nx] == mark){
                // 이전에 방문했던 곳일 경우
                if (visited[ny][nx] == group){
                    if (abs(check[ny][nx] - check[y][x]) >= 3){
                        circle = true;
                        dfs(mark, group, cnt + 1, ny, nx);
                    }
                }
                else if (visited[ny][nx] == 0){
                    dfs(mark, group, cnt+1, ny, nx);
                }
            }
        }
    }
}
int main(){
    cin>>sizeY>>sizeX;
    for(int i=0; i<sizeY; i++){
        string s;
        cin>>s;
        for(int j=0; j<sizeX; j++){
            map[i][j] = s[j];
        }
    }
    int group = 1;
    for(int y=0; y<sizeY; y++){
        for(int x=0; x<sizeX; x++){
            if (visited[y][x] == 0 && !circle){
                dfs(map[y][x], group, 0, y, x);
                if (circle) {
                    cout<<"Yes";
                }
                group++;
            }
        }
    }
    // printCheck();
    // cout<<"\n";
    // printVisited();
    if (!circle) cout<<"No";
}