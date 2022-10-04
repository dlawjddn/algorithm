#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;
char map[51][51];
int visited[51][51], move_x[6]={1,0,-1,-1,0,1}, move_y[6]={0,1,1,0,-1,-1}, ans=0, _size=0;
void dfs(int y, int x, int c){
    visited[y][x]=c;
    ans=max(ans, 1);
    for(int d=0; d<6; d++){
        int ny=y+move_y[d], nx=x+move_x[d];
        if (ny>0 && ny<=_size && nx>0 && nx<=_size && map[ny][nx]=='X'){
            if (visited[ny][nx]==-1) dfs(ny, nx, 1-c);
            ans=max(ans, 2);
            if (visited[ny][nx]==c) ans=max(ans, 3);
        }
    }
}
int main(){
    cin>>_size;
    for(int i=1; i<=_size; i++){
        string s;
        cin>>s;
        for(int j=1; j<=_size; j++){
            map[i][j]=s[j-1];
        }
    }
    memset(visited, -1, sizeof(visited));
    for(int a=1; a<=_size; a++){
        for(int b=1; b<=_size; b++){
            if (map[a][b]=='X' && visited[a][b]==-1) dfs(a, b, 0);
        }
    }
    cout<<ans;
}