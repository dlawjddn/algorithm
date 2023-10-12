#include <iostream>
#include <algorithm>
using namespace std;

struct Point{
    int y, x;
};
char map[15][15], ans[15][15];
int sizeX=0, sizeY=0, startX=0, startY=0, boxCount=0, success=0;
bool checkBound(Point pos){
    if (pos.y>0 && pos.y<sizeY-1 && pos.x>0 && pos.x<sizeX-1) return true;
    return false;
}
char nextWhat(int y, int x, char dir){
    if (dir=='U') return map[y-1][x];
    else if (dir == 'L') return map[y][x-1];
    else if (dir == 'R') return map[y][x+1];
    return map[y+1][x];
}
void printMap(){
    for(int a=0; a<sizeY; a++){
        for(int b=0; b<sizeX; b++){
            cout<<map[a][b];
        }
        cout<<"\n";
    }
    cout<<"\n";
}
int checkSuccess(){
    int cnt=0;
    for(int i=0; i<sizeY; i++){
        for(int j=0; j<sizeX; j++){
            if (map[i][j] == 'b' && ans[i][j] == '+') cnt++;
        }
    }
    return cnt;
}
Point nextPos(Point pos, char dir){
    Point next;
    if (dir == 'U'){
        next.y=pos.y-1;
        next.x=pos.x;
    }
    else if (dir=='D'){
        next.y=pos.y+1;
        next.x=pos.x;
    }
    else if (dir =='R'){
        next.y=pos.y;
        next.x=pos.x+1;
    }
    else{
        next.y=pos.y;
        next.x=pos.x-1;
    }
    return next;
}
bool playGame(string cmd){
    Point pos;
    pos.y=startY; pos.x=startX;
    for(int i=0; i<cmd.size(); i++){
        char nextBlock = nextWhat(pos.y, pos.x, cmd[i]);
        Point next = nextPos(pos, cmd[i]);
        if (!checkBound(next)) continue;
        if (nextBlock == '.' || nextBlock == '+') {
            swap(map[next.y][next.x], map[pos.y][pos.x]);
            pos = next;
        }
        else if (nextBlock == '#') continue;
        else if (nextBlock == 'b' || nextBlock == 'B'){
            char nnextBlock = nextWhat(next.y, next.x, cmd[i]);
            if (nnextBlock == '.' || nnextBlock == '+'){
                Point nnext = nextPos(next, cmd[i]);
                if (!checkBound(nnext)) continue;
                map[nnext.y][nnext.x]=map[next.y][next.x];
                map[next.y][next.x]=map[pos.y][pos.x];
                map[pos.y][pos.x]=ans[pos.y][pos.x];
                pos=next;
            }
            else continue;
        }
        if (boxCount == success) return true;
    }
    return false;
}
int main(){
    cin>>sizeY>>sizeX;
    int cnt=0;
    while((sizeY+sizeX)!=0){
        cnt++;
        for(int i=0; i<sizeY; i++){
            string s;
            cin>>s;
            for(int j=0; j<sizeX; j++){
                map[i][j]=s[j];
                ans[i][j]=s[j];
                if (map[i][j]=='w'){
                    startY=i; startX=j;
                    ans[i][j] = '.';
                }
                else if (ans[i][j] == 'b') {
                    ans[i][j]='.';
                }
                else if (ans[i][j] == '+') boxCount++;
            }
        }
        string cmd;
        cin>>cmd;
        bool result = playGame(cmd);
        cout<<boxCount<<" "<<success<<"\n";
        cout<<"Game " << cnt << ": ";
        if (result) cout<<"complete\n";
        else cout<<"incomplete\n";
        for(int i=0; i<sizeY; i++){
            for(int j=0; j<sizeX; j++){
                if (ans[i][j] == '+' && map[i][j] == 'w') cout<<'W';
                else if (ans[i][j] == '+' && map[i][j] == 'b') cout<<'B';
                else cout<<map[i][j];
            }
            cout<<"\n";
        }
        cin>>sizeY>>sizeX;
    }
}