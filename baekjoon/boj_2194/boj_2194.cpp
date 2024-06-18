#include <iostream>
#include <queue>
using namespace std;
queue<pair<int, int> > q;
int map[510][510], visited[510][510], move_y[4]={0,1,0,-1}, move_x[4]={1,0,-1,0}, size_x=0, size_y=0, unit_x=0, unit_y=0, start_y=0, start_x=0, end_y=0, end_x=0, wall=0;
int check_path(int y, int x){
    for(int i=y; i<(y+unit_y); i++){
        for(int j=x; j<(x+unit_x); j++){
            if (map[i][j]==1) return 0;
        }
    }
    return 1;
}
int use_bfs(){
    q.push(make_pair(start_y, start_x));
    visited[start_y][start_x]=1;
    while(!q.empty()){
        int y=q.front().first;
        int x=q.front().second; q.pop();
        if (y==end_y && x==end_x) return visited[y][x]-1;
        for(int d=0; d<4; d++){
            int ny=y+move_y[d], nx=x+move_x[d];
            if (ny>0 && ny<=(size_y-unit_y+1) && nx>0 && nx<=(size_x-unit_x+1) && check_path(ny, nx) && !visited[ny][nx]){
                visited[ny][nx]=visited[y][x]+1;
                q.push(make_pair(ny, nx));
            }
        }
    }
    return -1;
}
int main(){
    cin>>size_y>>size_x>>unit_y>>unit_x>>wall;
    for(int i=0; i<wall; i++){
        int temp_y=0, temp_x=0;
        cin>>temp_y>>temp_x;
        map[temp_y][temp_x]=1;
    }
    cin>>start_y>>start_x>>end_y>>end_x;
    cout<<use_bfs();
}