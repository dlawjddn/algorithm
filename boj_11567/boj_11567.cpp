#include <iostream>
#include <queue>
using namespace std;
char map[505][505];
int visited[505][505], move_y[4]={0,1,0,-1}, move_x[4]={1,0,-1,0}, size_y=0, size_x=0, start_y=0, start_x=0, end_y=0, end_x=0;
void after_visited_dest(){
    for(int d=0; d<4; d++){
        int ny=end_y+move_y[d], nx=end_x+move_x[d];
        if (ny>=0 && ny<size_y && nx>=0 && nx<size_x && map[ny][nx]=='.'){
            cout<<"YES";
            return ;
        }
    }
    cout<<"NO";
}
void check_real_path(){
    queue<pair<int, int> > q;
    q.push(make_pair(end_y, end_x));
    map[end_y][end_x]='X';
    while(!q.empty()){
        int y=q.front().first;
        int x=q.front().second; q.pop();
        for(int d=0; d<4; d++){
            int ny=y+move_y[d], nx=x+move_x[d];
            if (ny>=0 && ny<size_y && nx>=0 && nx<size_x && visited[ny][nx]==visited[y][x]-1 && visited[ny][nx]>=1){
                map[ny][nx]='X';
                q.push(make_pair(ny, nx));
                break;
            }
        }
    }
}
int first_find_path(){
    queue<pair<int, int> > q;
    q.push(make_pair(start_y, start_x));
    visited[start_y][start_x]=1;
    while(!q.empty()){
        int y=q.front().first;
        int x=q.front().second; q.pop();
        for(int d=0; d<4; d++){
            int ny=y+move_y[d], nx=x+move_x[d];
            if (ny==end_y && nx==end_x){
                visited[ny][nx]=visited[y][x]+1;
                return 1;
            }
            if (ny>=0 && ny<size_y && nx>=0 && nx<size_x && visited[ny][nx]==0 && map[ny][nx]=='.'){
                visited[ny][nx]=visited[y][x]+1;
                q.push(make_pair(ny, nx));
            }
        }
    }
    return 0;
}
int main(){
    cin>>size_y>>size_x;
    for(int i=0; i<size_y; i++) {
        cin>>map[i];
        for(int j=0; j<size_x; j++){
            if (map[i][j]=='X') visited[i][j]=-1;
        }
    }
    cin>>start_y>>start_x>>end_y>>end_x;
    start_y-=1; start_x-=1; end_y-=1, end_x-=1;
    if (visited[end_y][end_x]==-1){
        if (first_find_path()) cout<<"YES";
        else cout<<"NO";
    }
    else{
        if (first_find_path()){
            check_real_path();
            after_visited_dest();
        }
        else cout<<"NO";
    }
}
