#include <iostream>
#include <queue>
using namespace std;
struct Point{
    int x, y, wall;
};
int map[1001][1001], visited[1001][1001][2], move_x[4]={1,0,-1,0}, move_y[4]={0,1,0,-1}, size_y=0, size_x=0, start_x=0, start_y=0, end_y=0, end_x=0;
int use_bfs(){
    queue<Point> q;
    Point start;
    start.y=start_y; start.x=start_x; start.wall=0;
    q.push(start);
    visited[start_y][start_x][start.wall]=1;
    while(!q.empty()){
        Point temp=q.front(); q.pop();
        for(int d=0; d<4; d++){
            Point next;
            next.y=temp.y+move_y[d], next.x=temp.x+move_x[d], next.wall=temp.wall;
            if (next.y>0 && next.y<=size_y && next.x>0 && next.x<=size_x){
                if (next.y==end_y && next.x==end_x) return visited[temp.y][temp.x][temp.wall];
                if (map[next.y][next.x]==0 && visited[next.y][next.x][next.wall]==0){
                    q.push(next);
                    visited[next.y][next.x][next.wall]=visited[temp.y][temp.x][temp.wall]+1;
                }
                else if (map[next.y][next.x]==1 && next.wall==0 && visited[next.y][next.x][next.wall+1]==0){
                    next.wall+=1;
                    q.push(next);
                    visited[next.y][next.x][next.wall]=visited[temp.y][temp.x][temp.wall]+1;
                }
            }
        }
    }
    return -1;
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin>>size_y>>size_x>>start_y>>start_x>>end_y>>end_x;
    for(int i=1; i<=size_y; i++){
        for(int j=1; j<=size_x; j++){
            cin>>map[i][j];
        }
    }
    cout<<use_bfs();
}