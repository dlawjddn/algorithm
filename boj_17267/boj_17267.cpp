#include <iostream>
#include <queue>
using namespace std;
int map[1000][1000], moveY[4]={-1,1,0,0}, moveX[4]={0,0,1,-1}, l=0, r=0, ans=0, sizeX=0, sizeY=0;
bool visited[1000][1000];
struct Info{
    int y, x, left, right;
};
queue<Info> q;
bool checkBound(int y, int x){
    if (y>=0 && y<sizeY && x>=0 && x<sizeX) return true;
    return false;
}
void UP_Down_Push(Info temp){
    bool uFlag=false, dFlag=false, tFlag=false;
    int cnt=1;
    while(!tFlag){
        for(int d=0; d<2; d++){
            if ((d==0 && uFlag) || (d==1&& dFlag)) continue;
            Info next=temp;
            next.y=temp.y+(moveY[d]*cnt);
            next.x=temp.x+(moveX[d]*cnt);
            if (checkBound(next.y, next.x) && map[next.y][next.x]==0){
                if (!visited[next.y][next.x]){
                    q.push(next);
                    visited[next.y][next.x]=true;
                    ans++;
                }
            }
            else{
                if (d==0) uFlag=true;
                else dFlag=true;
                if (uFlag && dFlag) tFlag=true;
            }
        }
        cnt++;
    }
}
void Left_Push(Info temp){
    Info next;
    next.y=temp.y+moveY[3];
    next.x=temp.x+moveX[3];
    if (checkBound(next.y, next.x) && map[next.y][next.x]==0 && temp.left>0 && !visited[next.y][next.x]){
        next.left=temp.left-1;
        next.right=temp.right;
        q.push(next);
        visited[next.y][next.x]=true;
        ans++;
    }
}
void Right_Push(Info temp){
    Info next;
    next.y=temp.y+moveY[2];
    next.x=temp.x+moveX[2];
    if (checkBound(next.y, next.x) && map[next.y][next.x]==0 && temp.right>0 && !visited[next.y][next.x]){
        next.left=temp.left;
        next.right=temp.right-1;
        q.push(next);
        visited[next.y][next.x]=true;
        ans++;
    }
}
void use_bfs(int startY, int startX){
    Info start;
    start.y=startY; start.x=startX, start.left=l, start.right=r;
    q.push(start);
    visited[startY][startX]=true;
    ans++;
    while(!q.empty()){
        Info temp=q.front(); q.pop();
        UP_Down_Push(temp);
        Left_Push(temp);
        Right_Push(temp);
    }
}
int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int startY=0, startX=0;
    cin>>sizeY>>sizeX>>l>>r;
    for(int y=0; y<sizeY; y++){
        string str;
        cin>>str;
        for(int x=0; x<sizeX; x++){
            map[y][x]=str[x]-'0';
            if (map[y][x]==2){
                startY=y;
                startX=x;
            }
        }
    }
    use_bfs(startY, startX);
    cout<<ans;
}