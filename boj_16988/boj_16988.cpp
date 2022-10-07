#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;
struct Point{
    int x, y;
};
Point empty_pos[400];
int map[20][20], temp_map[20][20], visited[20][20], com[2], move_x[4]={1,0,-1,0}, move_y[4]={0,1,0,-1}, size_x=0, size_y=0, empty_block=0, cnt=0, start_y=0, start_x=0, ans=0;
int use_bfs(){
    int temp_cnt=0;
    bool flag=false;
    queue<pair<int, int> > q;
    q.push(make_pair(start_y, start_x));
    visited[start_y][start_x]=1;
    while(!q.empty()){
        int y=q.front().first;
        int x=q.front().second; q.pop();
        temp_cnt++;
        for(int d=0; d<4; d++){
            int ny=y+move_y[d], nx=x+move_x[d];
            if (ny>=0 && ny<size_y && nx>=0 && nx<size_x && !visited[ny][nx]){
                if (temp_map[ny][nx]==1) continue;
                else if (temp_map[ny][nx]==2){
                    visited[ny][nx]=1;
                    q.push(make_pair(ny, nx));
                }
                else if (temp_map[ny][nx]==0) flag=true;
            }
        }
    }
    if (flag) return 0;
    else return temp_cnt;
}
void kill_enemy(){
    cnt=0;
    copy(&map[0][0], &map[0][0]+400, &temp_map[0][0]);
    temp_map[empty_pos[com[0]].y][empty_pos[com[0]].x]=1;
    temp_map[empty_pos[com[1]].y][empty_pos[com[1]].x]=1;
    for(int y=0; y<size_y; y++){
        for(int x=0; x<size_x; x++){
            if (temp_map[y][x]==2 && visited[y][x]==0){
                start_y=y; start_x=x;
                cnt+=use_bfs();
            }
        }
    }
    ans=max(ans, cnt);
}
void find_out(int num, int _cnt){
    if (_cnt == 1){
        kill_enemy();
        memset(visited, 0, sizeof(visited));
        memset(temp_map, 0, sizeof(temp_map));
        return ;
    }
    else{
        _cnt+=1;
        for(int i=num+1; i<empty_block; i++){
            com[_cnt]=i;
            find_out(i, _cnt);
        }
    }
}
void play_baduk(){
    for(int i=0; i<empty_block; i++){
        com[0]=i;
        find_out(i, 0);
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin>>size_y>>size_x;
    for(int i=0; i<size_y; i++){
        for(int j=0; j<size_x; j++){
            cin>>map[i][j];
            if (map[i][j]==0){
                empty_pos[empty_block].y=i;
                empty_pos[empty_block].x=j;
                empty_block++;
            }
        }
    }
    play_baduk();
    cout<<ans;
}