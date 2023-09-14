#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

int map[50][50];
int visited[50][50];
int each_room_size[2501];
int moveX[4]={-1, 0, 1, 0}, moveY[4]={0,-1,0,1}, sizeY=0, sizeX=0, roomSize=0, roomCnt=0, afterBreakSize=0;

bool checkBound(int y, int x){
    return y>=0 && y<sizeY && x>=0 && x<sizeX;
}

int check_room_size(int startY, int startX){
    int tempSize = 1;
    queue<pair<int, int> > q;
    q.push(make_pair(startY, startX));
    visited[startY][startX] = 1;
    while(!q.empty()){
        int y = q.front().first;
        int x = q.front().second; q.pop();
        int wall = 1;
        for(int d=0; d<4; d++){
            if ((map[y][x] & wall) != wall){
                int ny = y + moveY[d];
                int nx = x + moveX[d];
                if (checkBound(ny, nx) && !visited[ny][nx]){
                    q.push(make_pair(ny, nx));
                    visited[ny][nx] = ++tempSize;
                }
            }
            wall *= 2;

        }
    }
    return tempSize;
}
void check_room(){
    for(int i=0; i<sizeY; i++){ // 기존 벽을 유지한 상태에서의 결과값
        for(int j=0; j<sizeX; j++){
            if (!visited[i][j]){
                roomCnt++;
                int tempSize = check_room_size(i,j);
                each_room_size[roomSize] = tempSize; 
                roomSize = max(roomSize, tempSize);
            }
        }
    }
    cout<<"\n";
    for(int a=0; a<sizeY; a++){
        for(int b=0; b<sizeX; b++){
            cout<<visited[a][b]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";
    // 하나씩 벽을 부순 다음 확인하는 결과값
    int wall = 1;
    for(int y=0; y<sizeY; y++){
        for(int x=0; x<sizeX; x++){
            if ((map[y][x] & wall) == wall){ // 해당 위치가 벽이라면
                memset(visited, 0, sizeof(visited));
                map[y][x] -= wall;
                afterBreakSize = max(afterBreakSize, check_room_size(y, x));
                map[y][x] += wall;
            }
        }
    }
}

int main(){
    cin>>sizeX>>sizeY;
    for(int i=0; i<sizeY; i++){
        for(int j=0; j<sizeX; j++){
            cin>>map[i][j];
        }
    }
    check_room();
    for(int i = 0; i<roomCnt; i++){
        cout<<each_room_size[i]<<" ";
    }
    cout<<"\n";
    cout<<roomCnt<<"\n"<<roomSize<<"\n"<<afterBreakSize;
}