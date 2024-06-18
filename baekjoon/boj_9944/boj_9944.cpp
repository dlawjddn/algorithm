// 50퍼에서 오답 진짜 죽어도 모르겠음..
#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
struct Info{
    int y, x, cnt, move;
    int visited[30][30];
};
char map[30][30];
int move_x[4]={1,0,-1,0}, move_y[4]={0,1,0,-1}, size_y=0, size_x=0, ans=1000000, empty_cnt=0;
int use_bfs(int y, int x){
    Info start;
    start.y=y; start.x=x, start.cnt=1;
    memset(start.visited, 0, sizeof(start.visited));
    start.visited[start.y][start.x]=1;
    if (start.cnt==empty_cnt) return 0;
    queue<Info> q;
    q.push(start);
    while(!q.empty()){
        Info temp=q.front(); q.pop();
        for(int d=0; d<4; d++){
            Info next = temp;
            copy(&temp.visited[0][0], &temp.visited[0][0] + 900, &next.visited[0][0]);
            while(1){
                next.y+=move_y[d]; next.x+=move_x[d];
                if (next.y>=0 && next.y<size_y && next.x>=0 && next.x<size_x && map[next.y][next.x]!='*' &&next.visited[next.y][next.x]==0){
                    next.visited[next.y][next.x]=next.visited[temp.y][temp.x]+1;
                    next.cnt++;
                }
                else{
                    next.y-=move_y[d]; next.x-=move_x[d];
                    if (temp.cnt!=next.cnt) next.move++;
                    else break;
                    if (next.cnt==empty_cnt) return next.move-2;
                    q.push(next);
                    break;
                }
            }
        }
    }
    return -1;
}
void check_every(){
    for(int i=0; i<size_y; i++){
        for(int j=0; j<size_x; j++){
            if (map[i][j]=='.'){
                int temp_max = use_bfs(i, j);
                if (temp_max>=0) {
                    ans=min(ans, temp_max);
                } 
            }
        }
    }
}
int main(){
    int repeat=1;
    while(cin>>size_y>>size_x){
        memset(map, 0, sizeof(map));
        ans=1000000;
        empty_cnt=0;
        for(int i=0; i<size_y; i++){
            string s;
            cin>>s;
            for(int j=0; j<size_x; j++){
                map[i][j]=s[j];
                if (map[i][j]=='.') empty_cnt++;
            }
        }
        check_every();
        if (ans==1000000) cout<<"Case "<<repeat++<<": -1\n";
        else cout<<"Case "<<repeat++<<": "<<ans<<"\n";
    }
}