#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

queue<pair<int, int> > q;
int map[101][101], visited[101][101], moveX[4]={1,0,-1,0}, moveY[4]={0,1,0,-1};

// 아이템 줍기
void fillRec(int startY, int startX, int endY, int endX) {
    for(int i=startY; i<=endY; i++){
        for(int j=startX; j<=endX; j++){
            map[i][j] = 1;
        }
    }
}

void dig(int startY, int startX, int endY, int endX){
    for(int i=startY+1; i<=endY-1; i++){
        for(int j=startX+1; j<=endX-1; j++){
            map[i][j] = 0;
        }
    }
}

int bfs(int y, int x, int ix, int iy){
    q.push(make_pair(y,x));
    visited[y][x] = 1;
    while(!q.empty()){
        int y = q.front().first;
        int x = q.front().second; q.pop();
        if (ix == x && iy == y) return visited[y][x];
        for(int d=0; d<4; d++){
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            if (ny >= 0 && ny <= 100 && nx >=0 && nx <= 100 && map[ny][nx] == 1 && visited[ny][nx] == 0){
                q.push(make_pair(ny, nx));
                visited[ny][nx] = visited[y][x] + 1;
            }
        }
    }
    return 0;
}

int solution(vector<vector<int>> rectangle, int characterX, int characterY, int itemX, int itemY) {
    int answer = 0;
    for(int i=0; i<rectangle.size(); i++)
        fillRec(rectangle[i][1] * 2, rectangle[i][0]*2, rectangle[i][3]*2, rectangle[i][2]*2);
    for(int i=0; i<rectangle.size(); i++)
        dig(rectangle[i][1] * 2, rectangle[i][0]*2, rectangle[i][3]*2, rectangle[i][2]*2);
     
    return bfs(characterY * 2, characterX * 2, itemX * 2, itemY * 2) / 2;
    // for(int i=0; i<50; i++){
    //     for(int j=0; j<50; j++){
    //         cout<<visited[i][j];
    //     }
    //     cout<<"\n";
    // }
    // return answer / 2;
}