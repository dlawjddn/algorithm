#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
char map[50][50];
int visited[50][50][2500], moveX[4]={1,0,-1,0}, moveY[4]={0,1,0,-1}, sizeSQ=0, ans=25000;
struct Info{
    int y, x, broken;
};
bool checkBound(int y, int x){
    if (y>=0 && y<sizeSQ && x>=0 && x<sizeSQ) return true;
    return false;
}
void use_bfs(){
    Info start;
    start.y=0;
    start.x=0;
    start.broken=0;
    queue<Info> q;
    q.push(start);
    visited[0][0][0]=1;
    while(!q.empty()){
        Info temp = q.front(); q.pop();
        if (temp.y==sizeSQ-1 && temp.x==sizeSQ-1){
            ans = min(ans, visited[temp.y][temp.x][temp.broken]-1);
            continue;
        }
        for(int d=0; d<4; d++){
            Info next;
            next.y=temp.y+moveY[d];
            next.x=temp.x+moveX[d];
            next.broken=temp.broken;
            if (checkBound(next.y, next.x)){
                if (map[next.y][next.x]=='1' && !visited[next.y][next.x][next.broken]){
                    visited[next.y][next.x][next.broken]=visited[temp.y][temp.x][temp.broken];
                    q.push(next);
                }
                else if (map[next.y][next.x]=='0' && !visited[next.y][next.x][next.broken+1]){
                    next.broken++;
                    visited[next.y][next.x][next.broken]=visited[temp.y][temp.x][temp.broken]+1;
                    q.push(next);
                }
            }
        }
    }

}
int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>sizeSQ;
    for(int i=0; i<sizeSQ; i++){
        string str;
        cin>>str;
        for(int j=0; j<sizeSQ; j++){
            map[i][j]=str[j];
        }
    }
    use_bfs();
    cout<<ans;
}