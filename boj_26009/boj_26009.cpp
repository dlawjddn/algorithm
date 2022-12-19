#include <iostream>
#include <queue>
using namespace std;
int map[3002][3002], visited[3002][3002], move_x[4]={1,0,-1,0}, move_y[4]={0,1,0,-1}, group=0, size_y=0, size_x=0;
bool check_bound(int y, int x){
    if (y>0 && y<=size_y && x>0 && x<=size_x) return true;
    return false;
}
int find_path(){
    queue<pair<int, int > >q;
    q.push(make_pair(1, 1));
    map[1][1]=1;
    while(!q.empty()){
        int y=q.front().first;
        int x=q.front().second; q.pop();
        for(int d=0; d<4; d++){
            int ny=y+move_y[d], nx=x+move_x[d];
            if (check_bound(ny, nx)&& !visited[ny][nx] && !map[ny][nx]){
                q.push(make_pair(ny, nx));
                map[ny][nx]=map[y][x]+1;
            }
        }
    }
    return map[size_y][size_x]; 
}
void check_traffic_jam(int start_y, int start_x, int dist){
    for(int a=dist; a>=0; a--){
        if (check_bound(start_y-(dist-a), start_x-a)) map[start_y-(dist-a)][start_x-a]=1;
        if (check_bound(start_y+(dist-a), start_x+a)) map[start_y+(dist-a)][start_x+a]=1;
        if (check_bound(start_y-(dist-a), start_x+a)) map[start_y-(dist-a)][start_x+a]=1;
        if (check_bound(start_y+(dist-a), start_x-a)) map[start_y+(dist-a)][start_x-a]=1;
    }
}
int main(){
    cin>>size_y>>size_x;
    cin>>group;
    for(int a=0; a<group; a++){
        int temp_x=0, temp_y=0, temp_dist=0;
        cin>>temp_y>>temp_x>>temp_dist;
        check_traffic_jam(temp_y, temp_x, temp_dist);
    }
    if(!find_path()) cout<<"NO";
    else cout<<"YES\n"<<map[size_y][size_x]-1;
}