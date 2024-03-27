#include <iostream>
#include <queue>
using namespace std;

struct Point{
    int y, x, dir;
};
int map[50][50], visited[50][50], moveX[8]={0,1,0,-1,0,1,0,-1}, moveY[8]={-1,0,1,0,-1,0,1,0}, sizeX=0, sizeY=0, cnt=1;

void printMap(int sizeY, int sizeX){
    for(int y=0; y<sizeY; y++){
        for(int x=0; x<sizeX; x++){
            cout<<map[y][x]<<" ";
        }
        cout<<"\n";
    }
}
void clean_room(Point start){
    queue<Point> q;
    q.push(start);
    visited[start.y][start.x] = 1;
    // 시작점은 항상 청소가 가능하기 때문에 제외

    bool all_stop = false;
    while(!q.empty()){
        Point now = q.front(); q.pop();
        bool go_back = true; //  주변에 청소할 곳이 없는 경우 -> 후진 해야함
        for(int d=0; d<4; d++){
            Point next;
            next.dir = (now.dir + 3 - d) % 4;
            next.y = now.y + moveY[next.dir];
            next.x = now.x + moveX[next.dir];
            // 해당 칸이 범위에 존재하고, 벽이 아니고, 청소를 하지 않았다
            if (next.y >=0 && next.y<sizeY && next.x>=0 && next.x<sizeX && map[next.y][next.x] == 0 && visited[next.y][next.x] == 0){
                q.push(next);
                visited[next.y][next.x] = 1;
                cnt += 1;
                go_back = false;
                break;
            }
        }
        // 4방향 모두 청소할 곳이 없어서 후진을 해야하는 경우
        if (go_back){
            Point next;
            next.dir = now.dir;
            next.y = now.y + moveY[(next.dir +2) % 4];
            next.x = now.x + moveX[(next.dir +2) % 4];
            if (next.y >=0 && next.y<sizeY && next.x>=0 && next.x<sizeX && map[next.y][next.x] == 0){
                q.push(next);
                if (visited[next.y][next.x] == 0) {
                    visited[next.y][next.x] = 1;
                    cnt += 1;
                }
            } 
            else all_stop = true;
        }
        if (all_stop){
            cout<<cnt;
            return ;
        }
    }
}
int main(){
    int startY, startX, startD;
    cin>>sizeY>>sizeX;
    cin>>startY>>startX>>startD;
    for(int y=0; y<sizeY; y++){
        for(int x=0; x<sizeX; x++){
            cin>>map[y][x];
        }
    }
    Point start;
    start.y = startY;
    start.x = startX;
    start.dir = startD;
    clean_room(start);
}