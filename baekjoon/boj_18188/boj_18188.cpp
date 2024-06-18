#include <iostream>
#include <queue>
#include <string>
using namespace std;
struct info{
    int y, x;
    string path;
};
char map[22][22];
int visited[21][21], obstruct[21][2], move_x[4]={0,1,0,-1}, move_y[4]={-1,0,1,0}, size_y=0, size_x=0, moving=0, start_y=0, start_x=0;
void go_for_love(){
    queue<info> q;
    info start;
    start.y=start_y, start.x=start_x, start.path="";
    q.push(start);
    visited[start.y][start.x]=1;
    while(!q.empty()){
        info now=q.front(); q.pop();
        int now_dist=visited[now.y][now.x];
        if (now_dist>moving) continue;
        int cant_go1=obstruct[now_dist-1][0], cant_go2=obstruct[now_dist-1][1];
        for(int d=0; d<4; d++){
            if (d!=cant_go1 && d!=cant_go2) continue;
            info next;
            next.y=now.y+move_y[d], next.x=now.x+move_x[d], next.path=now.path;
            if (d==0) next.path+='W';
            else if (d==1) next.path+='D';
            else if (d==2) next.path+='S';
            else next.path+='A';
            if (next.y>0 && next.y<=size_y && next.x>0 && next.x<=size_x && map[next.y][next.x]!='@'){
                if (map[next.y][next.x]=='Z'){
                    cout<<"YES\n"<<next.path;
                    return ;
                }
                visited[next.y][next.x]=visited[now.y][now.x]+1;
                q.push(next);
            }
        }
    }
    cout<<"NO";
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin>>size_y>>size_x;
    for(int i=1; i<=size_y; i++){
        string s;
        cin>>s;
        for(int j=1; j<=size_x; j++){
            map[i][j]=s[j-1];
            if (map[i][j]=='D'){
                start_y=i; start_x=j;
            }
        }
    }
    cin>>moving;
    for(int a=0; a<moving; a++){
        for(int b=0; b<2; b++){
            char dire;
            cin>>dire;
            if (dire=='W') obstruct[a][b]=0;
            else if (dire=='D') obstruct[a][b]=1;
            else if (dire=='S') obstruct[a][b]=2;
            else obstruct[a][b]=3;
        }
    }
    go_for_love();
}