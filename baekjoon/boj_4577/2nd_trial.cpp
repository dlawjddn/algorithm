#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

char map[15][15], first[15][15];
int sizeX=0, sizeY=0, goalCount=0, success=0;
struct Point{
    int y, x;
};
void printAnsMap(){
    for(int i=0; i<sizeY; i++){
        for(int j=0; j<sizeX; j++){
            cout<<map[i][j];
        }
        cout<<"\n";
    }
}
Point nextPoint(Point pos, char dir){
    Point next;
    if (dir == 'U'){
        next.y=pos.y-1;
        next.x=pos.x;
    }
    else if (dir == 'D'){
        next.y=pos.y+1;
        next.x=pos.x;
    }
    else if (dir == 'R'){
        next.y=pos.y;
        next.x=pos.x+1;
    }
    else {
        next.y=pos.y;
        next.x=pos.x-1;
    }
    return next;
}
char shapeOfBlock(Point pos, char dir){
    return map[pos.y][pos.x];
}

Point moving(Point pos, char dir){
    Point next = nextPoint(pos, dir);
    // 일반적인 이동
    if (map[next.y][next.x]=='.' || map[next.y][next.x]=='+') swap(map[pos.y][pos.x], map[next.y][next.x]);
    //벽을 만난 경우
    else if (map[next.y][next.x] == '#') return pos;
    //박스를 만난 경우
    else if (map[next.y][next.x] == 'b' || map[next.y][next.x]=='B'){
        Point nnext = nextPoint(next, dir); // 다다음 블록위치
        char shape = shapeOfBlock(nnext, dir);
        if (shape == 'b' || shape == '#') return pos;
        else if (shape == '.' || shape == '+'){
            map[nnext.y][nnext.x]=map[next.y][next.x];
            map[next.y][next.x]=map[pos.y][pos.x];
            map[pos.y][pos.x]=first[pos.y][pos.x];
        }
    }
    return next;
}
void checkSucess(Point pos, Point next, char before){
    if (map[pos.y][pos.x] == 'b' && first[pos.y][pos.x] == '+') success++;
    
}

bool playGame(string cmd, int startY, int startX){
    Point pos;
    pos.y=startY;
    pos.x=startX;
    for(int i=0; i<cmd.size(); i++){
        printAnsMap();
        cout<<"\n";
        if (goalCount == success) return true;
        pos = moving(pos, cmd[i]);
    }
    return false;
}

int main(){
    int cnt=0, startY=0, startX=0;
    while(1){
        cnt++;
        memset(&map, 0, sizeof(map));
        memset(&first, 0, sizeof(first));
        cin>>sizeY>>sizeX;
        if (sizeY==0 && sizeX==0) break;
        for(int i=0; i<sizeY; i++){
            string temp;
            cin>>temp;
            for(int j=0; j<sizeX; j++){
                map[i][j] = temp[j];
                first[i][j] = temp[j];
                if (first[i][i] != '.' || first[i][j]!= '#' || first[i][j] != '+'){
                    if (first[i][j]>='A' && first[i][j] <= 'Z') first[i][j]='+';
                    else if (first[i][j] >='a' && first[i][j] <='z') first[i][j]='.';
                }
                if ((map[i][j]>='A' && map[i][j] <='Z') || map[i][j] == '+') {
                    goalCount++;
                    if (map[i][j] == 'B'){
                        success++;
                    }
                }
                if (map[i][j] == 'w' || map[i][j] == 'W'){
                    startY=i;
                    startX=j;
                }
            }
        }
        for(int i=0; i<sizeY; i++){
            for(int j=0; j<sizeX; j++){
                cout<<first[i][j];
            }
            cout<<"\n";
        }
        string cmd;
        cin>>cmd;
        bool result = playGame(cmd, startY, startX);
        if (result) cout<<"Game "<<cnt<<": complete\n";
        else cout<<"Game "<<cnt<<": incomplete\n";
        printAnsMap();
    }
}