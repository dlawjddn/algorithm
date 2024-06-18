#include <iostream>
#include <queue>
using namespace std;
bool visited[50][50][4][2][2];
char map[50][50];
int moveX[5]={1,0,-1,0,0}, moveY[5]={0,1,0,-1,0}, sizeX=0, sizeY=0, ans=0;
struct Info{
    int y, x, before, times;
    bool cFlag, dFlag;
};
Info start;
bool checkBound(int y, int x){
    if (y>=0 && y<sizeY && x>=0 && x<sizeX) return true;
    return false;
}
void checkPath(Info start){
    queue<Info> q;
    q.push(start);
    while(!q.empty()){
        Info temp = q.front(); q.pop();
        if (temp.cFlag && temp.dFlag){
            ans=temp.times;
            return ;
        }
        for(int d=0; d<4; d++){
            if (temp.before == d) continue;
            Info next;
            next.y=temp.y+moveY[d];
            next.x=temp.x+moveX[d];
            next.before=d;
            next.times=temp.times+1;
            next.cFlag=temp.cFlag;
            next.dFlag=temp.dFlag;
            if (checkBound(next.y, next.x) && map[next.y][next.x]!='#' && !visited[next.y][next.x][next.before][next.cFlag][next.dFlag]){
                if (map[next.y][next.x]=='C') next.cFlag=true;
                if (map[next.y][next.x]=='D') next.dFlag=true;
                q.push(next);
                visited[next.y][next.x][next.before][next.cFlag][next.dFlag]=true;
            }
        }
    }
}
int main(){
    bool first=false;
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>sizeY>>sizeX;
    start.before=-1; start.times=0; start.cFlag=false; start.dFlag=false;
    for(int i=0; i<sizeY; i++){
        string str;
        cin>>str;
        for(int j=0; j<sizeX; j++){
            map[i][j]=str[j];
            if (map[i][j]=='S'){
                start.y=i;
                start.x=j;
                start.before=-1;
                start.times=0;
                start.cFlag=false;
                start.dFlag=false;
            }
            else if (map[i][j]=='C'){
                if (first) map[i][j]='D';
                first=true;
            }
        }
    }
    checkPath(start);
    if (ans==0) cout<<"-1";
    else cout<<ans;
}