#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;

int map[15][15], changed[15][15], moveX[8]={1,1,0,-1,-1,-1,0,1}, moveY[8] = {0,-1,-1,-1,0,1,1,1}, size = 0, year = 0;
queue<pair<int, int> > move_q;

void moving(int d, int time, int y, int x){
    int tempY = y, tempX = x;
    //cout<<"startY: "<<tempY<<" startX: "<<tempX<<"\n";
    for(int i = 0; i<time; i++){
        int ny = tempY + moveY[d-1];
        int nx = tempX + moveX[d-1];
        if (ny < 0 || ny >= size){
            if (ny < 0){
                ny = size - 1;
            } else {
                ny = 0;
            }
        }
        if (nx < 0 || nx >= size){
            if (nx < 0){
                nx = size - 1;
            } else {
                nx = 0;
            }
        }
        tempY = ny;
        tempX = nx;
    }
    //cout<<"finalY: "<<tempY<<" finalX: "<<tempX<<"\n";
    map[tempY][tempX] += 1;
    move_q.push(make_pair(tempY, tempX));
}

void process1(int d, int time){
    int t = move_q.size();
    for(int i=0; i<t; i++){
        moving(d, time, move_q.front().first, move_q.front().second);
        move_q.pop();
    }
}
void process2(){
    while(!move_q.empty()){
        int y = move_q.front().first;
        int x = move_q.front().second; move_q.pop();
        int cnt = 0;
        for(int d=1; d<=7; d+=2){
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            if (ny >=0 && ny<size && nx >=0 && nx <size && map[ny][nx] > 0) cnt++;
        }
        changed[y][x] = 1;
        map[y][x] += cnt;
    }
}
int process3(){
    int ans = 0;
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            if (changed[i][j] == 0 && map[i][j] >= 2){
                map[i][j] -= 2;
                move_q.push(make_pair(i,j));
            }
            ans += map[i][j];
        }
    }
    return ans;
}
void printMap(){
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            cout<<map[i][j]<<" ";
        }
        cout<<"\n";
    }
}
void printChanged(){
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            cout<<changed[i][j]<<" ";
        }
        cout<<"\n";
    }
}
int main() {
    cin>>size>>year;
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            cin>>map[i][j];
        }
    }
    move_q.push(make_pair(size-1, 0));
    move_q.push(make_pair(size-2, 0));
    move_q.push(make_pair(size-1, 1));
    move_q.push(make_pair(size-2, 1));
    for(int i=0; i<year; i++){
        int dir = 0, times = 0, ans = 0;
        cin>>dir>>times;
        process1(dir, times);
        process2();
        ans = process3();
        memset(changed, 0, sizeof(changed));
        if (i == year - 1) cout<<ans;
    }
    return 0;
}