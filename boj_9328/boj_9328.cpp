#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
struct Pos{
    int y, x;
};
Pos start[400];
char map[100][100];
bool key[26], stop=true;
int total=0, size_y=0, size_x=0, visited[100][100], move_y[4]={0,1,0,-1}, move_x[4]={1,0,-1,0}, ans=0;
void use_bfs(int cnt){
    memset(visited, 0, sizeof(visited));
    queue<Pos> q;
    for(int i=0; i<cnt; i++){
        if (map[start[i].y][start[i].x]>='A' && map[start[i].y][start[i].x]<='Z' && !key[map[start[i].y][start[i].x]-'A']) continue;
        if (map[start[i].y][start[i].x]=='$') {
            ans++;
            map[start[i].y][start[i].x]='.';
        }
        q.push(start[i]);
        visited[start[i].y][start[i].x]=1;
    }
    while(!q.empty()){
        Pos temp= q.front(); q.pop();
        for(int d=0; d<4; d++){
            Pos next;
            next.y=temp.y+move_y[d]; next.x=temp.x+move_x[d];
            if (next.y>=0 && next.y<size_y && next.x>=0 && next.x<size_x && !visited[next.y][next.x] && map[next.y][next.x]!='*'){
                if (map[next.y][next.x]=='.'){
                    q.push(next);
                    visited[next.y][next.x]=1;
                }
                else if (map[next.y][next.x]>='A' && map[next.y][next.x]<='Z' && key[map[next.y][next.x]-'A']){
                    q.push(next);
                    visited[next.y][next.x]=1;
                }
                else if (map[next.y][next.x]>='a' && map[next.y][next.x]<='z'){
                    if (!key[map[next.y][next.x]-'a']){
                        key[map[next.y][next.x]-'a']=true;
                        stop=false;
                        break;
                    }
                    else{
                        q.push(next);
                        visited[next.y][next.x]=1;
                    }
                }
                else if (map[next.y][next.x]=='$'){
                    ans++;
                    map[next.y][next.x]='.';
                    q.push(next);
                    visited[next.y][next.x]=1;
                }
            }
        }
    }
}
int main(){
    int cnt=0;
    cin>>total;
    for(int i=0; i<total; i++){
        cin>>size_y>>size_x;
        ans=0, cnt=0;
        memset(map, 0, sizeof(map));
        memset(visited, 0, sizeof(visited));
        memset(key, 0, sizeof(key));
        for(int y=0; y<size_y; y++){
            string s;
            cin>>s;
            for(int x=0; x<size_x; x++){
                map[y][x]=s[x];
                if ((y==0 || y==size_y-1 || x==0 || x==size_x-1) && map[y][x]!='*'){
                    start[cnt].y=y; start[cnt].x=x;
                    cnt++;
                }
            }
        }
        string start_key;
        cin>>start_key;
        for(int a=0; a<26; a++) {
            if (start_key[a]=='0') break;
            key[start_key[a]-'a']=true;
        }
        while(1){
            use_bfs(cnt);
            if (stop){
                cout<<ans<<"\n";
                break;
            }
            stop=true;
        }
    }
}
