#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

int map[50][50], visited[50][50], group_map[50][50], group_size[2501];
int moveX[4]={-1,0,1,0}, moveY[4]={0,-1,0,1};
int sizeX=0, sizeY=0, maxRoomCnt=0, maxRoomSize=0, maxAfterBreakSize=0;

bool checkBound(int y, int x){
    return y>=0 && y<sizeY && x>=0 && x<sizeX;
}

int check_size(int startY, int startX, int group_num){
    int roomSize = 1;
    queue<pair<int, int> > q;
    q.push(make_pair(startY, startX));
    visited[startY][startX] = 1;
    group_map[startY][startX] = group_num;
    while(!q.empty()){
        int y = q.front().first;
        int x = q.front().second; q.pop();
        int wall = 1;
        for(int d = 0; d<4; d++){
            if ((map[y][x] & wall) != wall){ // 벽이 아닌 경우
                int ny = y + moveY[d];
                int nx = x + moveX[d];
                if (checkBound(ny, nx) && !visited[ny][nx]){
                    q.push(make_pair(ny, nx));
                    visited[ny][nx] = visited[y][x] + 1;
                    roomSize++;
                    group_map[ny][nx] = group_num;
                }
            } 
            wall *= 2;
        }
    } 
    return roomSize;
}

void check_room(){
    // 벽을 부수기 전에 방의 개수와 가장 큰 방의 크기 구하기
    for(int i=0; i<sizeY; i++){
        for(int j=0; j<sizeX; j++){
            if (!visited[i][j]){
                int groupSize = check_size(i,j,++maxRoomCnt);
                group_size[maxRoomCnt] = groupSize;
                maxRoomSize = max(maxRoomSize, groupSize);
            }
        }
    }
    // 벽을 부순 후에 가장 큰 방의 크기 구하기
    for(int y=0; y<sizeY; y++){
        for(int x=0; x<sizeX; x++){
            for(int d=0; d<4; d++){
                int ny = y + moveY[d];
                int nx = x + moveX[d];
                if (checkBound(ny, nx) && group_map[ny][nx] != group_map[y][x]){ //  범위 벗어나면 안되고, 다른 그룹이여야 한다
                    maxAfterBreakSize = max(maxAfterBreakSize, (group_size[group_map[ny][nx]] + group_size[group_map[y][x]]));
                }
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
    cout<<maxRoomCnt<<"\n"<<maxRoomSize<<"\n"<<maxAfterBreakSize;
}