#include <iostream>
#include <queue>
#include <cmath>
#include <cstring>
using namespace std;
struct Point{
    int start_y, start_x, dest_y, dest_x;
};
Point guest_pos[401];
bool flag=false;
int map[21][21], visited[21][21], dx[4]={1,0,-1,0}, dy[4]={0,1,0,-1}, _size=0, guest=0, fuel=0, start_y=0, start_x=0, now_guest=0;
bool check_fuel(int num){
    if (!num || fuel<num-1){
        flag=true;
        cout<<"-1";
        return false;
    }
    return true;
}
void go_destination(){
    queue<pair<int, int> > q;
    q.push(make_pair(guest_pos[now_guest].start_y, guest_pos[now_guest].start_x));
    visited[guest_pos[now_guest].start_y][guest_pos[now_guest].start_x]=1;
    while(!q.empty()){
        int y=q.front().first;
        int x=q.front().second; q.pop();
        for(int d=0; d<4; d++){
            int ny=y+dy[d], nx=x+dx[d];
            if (ny>0 && ny<=_size && nx>0 && nx<=_size && !visited[ny][nx] && map[ny][nx]!=-1){
                visited[ny][nx]=visited[y][x]+1;
                q.push(make_pair(ny, nx));
            }
        }
    }
    if (!check_fuel(visited[guest_pos[now_guest].dest_y][guest_pos[now_guest].dest_x])) return ;
    else fuel+=(visited[guest_pos[now_guest].dest_y][guest_pos[now_guest].dest_x]-1);
    start_y=guest_pos[now_guest].dest_y; start_x=guest_pos[now_guest].dest_x;
    memset(visited, 0, sizeof(visited));
}
void find_the_closest_guest(){
    int close_dist=987654321;
    for(int a=1; a<=_size; a++){
        for(int b=1; b<=_size; b++){
            if(map[a][b]>0 && visited[a][b]<close_dist){
                now_guest=map[a][b];
                close_dist=visited[a][b];
                start_y=a, start_x=b;
            } 
        }
    }
    if (!check_fuel(close_dist)) return ;
    else fuel-=(close_dist-1);
    map[start_y][start_x]=0;
    memset(visited, 0, sizeof(visited));
}
void find_dist(){
    queue<pair<int, int> > q;
    q.push(make_pair(start_y, start_x));
    visited[start_y][start_x]=1;
    while(!q.empty()){
        int y=q.front().first;
        int x=q.front().second; q.pop();
        for(int d=0; d<4; d++){
            int ny=y+dy[d], nx=x+dx[d];
            if (ny>0 && ny<=_size && nx>0 && nx<=_size && !visited[ny][nx] && map[ny][nx]!=-1){
                visited[ny][nx]=visited[y][x]+1;
                q.push(make_pair(ny, nx));
            }
        }
    }
    find_the_closest_guest();
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin>>_size>>guest>>fuel;
    for(int i=1; i<=_size; i++){
        for(int j=1; j<=_size; j++){
            cin>>map[i][j];
            if (map[i][j]==1) map[i][j]=-1;
        }
    }
    cin>>start_y>>start_x;
    for(int k=1; k<=guest; k++){
        cin>>guest_pos[k].start_y>>guest_pos[k].start_x>>guest_pos[k].dest_y>>guest_pos[k].dest_x;
        map[guest_pos[k].start_y][guest_pos[k].start_x]=k;
    }
    for(int a=0; a<guest; a++){
        find_dist();
        if (flag) break;
        go_destination();
        if (flag) break;
    }
    if (!flag) cout<<fuel;
} 