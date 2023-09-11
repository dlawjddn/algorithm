#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

char map[8][8];
int moveX[9] = {0,1,1,0,-1,-1,-1,0,1}, moveY[9]={0,0,1,1,1,0,-1,-1,-1}, visited[8][8];
struct Point{
    int x, y;
};
queue<Point> q;
void dropWall(){
    for(int y=7; y>0; y--){
        for(int x=0; x<8; x++){
            if (y==7 && map[y][x] == '#'){
                map[y][x] = '.';
            }
            else{
                if (map[y-1][x] == '#'){
                    map[y][x] = '#';
                    map[y-1][x] = '.';
                }
            }
        }
    }
}
int checkMap(){
    int wallCnt=0;
    int personCnt=0;
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if (map[i][j] == 'p'){
                Point person;
                person.y = i;
                person.x = j;
                q.push(person);
                map[i][j] = '.';
                personCnt++;
            }
            if (map[i][j] == '#') wallCnt++;
        }
    }
    if (personCnt == 0) return -1;
    else if (wallCnt == 0 ) return 1;
    else return 0;
}
bool checkBound(int y, int x){
    if (y>=0 && y<8 && x>=0 && x<8) return true;
    return false;
}
void movingPerson(){
    while(!q.empty()){
        Point now = q.front(); q.pop();
        for(int d=0; d<9; d++){
            Point next;
            next.y=now.y+moveY[d];
            next.x=now.x+moveX[d];
            if (checkBound(next.y, next.x) && map[next.y][next.x] == '.'){
                map[next.y][next.x]='p';
            }
        }
    }
}
void setting(){
    Point start;
    start.y=7;
    start.x=0;
    q.push(start);
}
void printMap(){
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            cout<<map[i][j];
        }
        cout<<"\n";
    }
}
int main(){
    //input
    int check = 0;
    int cnt = 0; // wall count
    for(int i=0; i<8; i++){
        string s;
        cin>>s;
        for(int j=0; j<8; j++){
            map[i][j] = s[j];
        }
    }
    setting();
    while(check == 0){
        movingPerson();
        dropWall();
        //printMap();
        //cout<<"\n";
        check = checkMap();
        //printMap();
    }
    if (check == 1) cout<<"1";
    else cout<<"0";
}