#include <iostream>
#include <queue>

using namespace std;
struct Point{
    int y, x, cnt, stuff;
    Point(int y, int x, int cnt, int stuff) : x(x), y(y), cnt(cnt), stuff(stuff) {}
};
char map[50][50];
int visited[50][50][32], moveX[4]={1,0,-1,0}, moveY[4]={0,1,0,-1}, sizeY=0, sizeX=0, stuff_cnt=0;;

void printMap(int sizeY, int sizeX){
    for(int y=0; y<sizeY; y++){
        for(int x=0; x<sizeX; x++){
            cout<<map[y][x]<<" ";
        }
        cout<<"\n";
    }
}

void take_stuff(Point start){
    queue<Point> q;
    q.push(start);
    visited[start.y][start.x][start.stuff] = 1;
    while(!q.empty()){
        Point now = q.front(); q.pop();
        if (map[now.y][now.x] == 'E' && now.stuff == stuff_cnt){
            cout<<now.cnt;
            return;
        }
        for(int d=0; d<4; d++){
            int ny = now.y + moveY[d];
            int nx = now.x + moveX[d];
            // 범위에 존재하는지
            if (ny >=0 && ny < sizeY && nx >=0 && nx <sizeX){
                // 물건을 만난 경우
                if (map[ny][nx] >= '0' && map[ny][nx] <= '4'){
                    // 현재까지의 방문한 물건 초기화 (기존 물건 + 지금 방문한 물건을 비트 연산)
                    int next_stuff = now.stuff | (1 << map[ny][nx] - '0');
                    if (visited[ny][nx][next_stuff] == 0){
                        visited[ny][nx][next_stuff] = 1;
                        Point next(ny, nx, now.cnt+1, next_stuff);
                        q.push(next);
                    }
                }
                // 벽이 아닌 경우
                else if (map[ny][nx] != '#'){
                    int next_stuff = now.stuff;
                    if (visited[ny][nx][next_stuff] == 0){
                        visited[ny][nx][next_stuff] = 1;
                        Point next(ny, nx, now.cnt+1, next_stuff);
                        q.push(next);
                    }
                }
            }
        }

    }
}

int main(){
    int startY, startX;
    cin>>sizeX>>sizeY;
    for(int i=0; i<sizeY; i++){
        string s;
        cin>>s;
        for(int j=0; j<sizeX; j++){
            map[i][j] = s[j];
            if (map[i][j] == 'X'){
                map[i][j] = stuff_cnt++ + '0';
            }
            if (map[i][j] == 'S'){
                startY = i;
                startX = j;
            }
        }
    }
    stuff_cnt = (1 << stuff_cnt) - 1;
    //printMap(sizeY, sizeX);
    Point start(startY, startX, 0,0);
    take_stuff(start);
}