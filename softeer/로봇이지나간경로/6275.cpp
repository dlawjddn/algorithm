#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int sizeY = 0, sizeX = 0, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
int answerY = 0, answerX = 0, answer_len = 987654321, goal_cnt = 0;
string answer;
vector<string> map(25);

void print_map(){
    for(int y=0; y<sizeY; y++){
        for(int x=0; x<sizeX; x++){
            cout<<map[y][x]<<" ";
        }
        cout<<"\n";
    }
}

void print_visited(vector<vector<bool> > visited){
    for(int y=0; y<sizeY; y++){
        for(int x=0; x<sizeX; x++){
            cout<<visited[y][x]<<" ";
        }
        cout<<"\n";
    }
}

bool check_outside(int y, int x){
    return y < 0 || y >= sizeY || x < 0 || x >= sizeX;
}

void dfs(int startY, int startX, int y, int x, int dir, int len, string route, vector<vector<bool> > visited){
    visited[y][x] = true;
    // 정답보다 벌써 큰 경우
    if (route.size() > answer_len) return ;
    // 모든 점을 탐색한 경우
    if (len == goal_cnt){
        // print_visited(visited);
        // cout<<"\n";
        if (answer_len > route.size()){
            answerY = y;
            answerX = x;
            answer_len = route.size();
            answer = route;
            cout<<answer<<"\n";
            return ;
        }
    }
    // 직진, 좌회전, 우회전중에 선택하기
    // 직진
    bool stop = false;
    for(int i=1; i<=2; i++){
        int ny = y + (i * moveY[dir]);
        int nx = x + (i * moveX[dir]);
        if (check_outside(ny, nx) || visited[ny][nx] || map[ny][nx] == '.'){
            stop = true;
            break;
        }
    }
    if (!stop) {
        visited[y+moveY[dir]][x+moveX[dir]] = true;
        visited[y+moveY[dir]+moveY[dir]][x+moveX[dir]+moveX[dir]] = true;
        dfs(startY, startX, y + 2*moveY[dir], x + 2*moveX[dir], dir, len+2, route+"A", visited);
        return ;
        //visited[y+moveY[dir]][x+moveX[dir]] = false;
        //visited[y+moveY[dir]+moveY[dir]][x+moveX[dir]+moveX[dir]] = false;
        
    }
    // 회전하기
    for(int d=1; d<4; d+=2){
        int ny = y + moveY[(dir+d)%4];
        int nx = x + moveX[(dir+d)%4];
        if (check_outside(ny, nx) || visited[ny][nx] || map[ny][nx] == '.') continue;
        // 우회전
        if (d == 1){
            dfs(startY, startX, y, x, (dir+d)%4, len, route+"R", visited);
        }
        // 좌회전
        else if (d == 3){
            dfs(startY, startX, y, x, (dir+d)%4, len, route+"L", visited);
        }
    }
    //visited[y][x] = false;
}

void find_start(){
    for(int y=0; y<sizeY; y++){
        for(int x=0; x<sizeX; x++){
            if (map[y][x] == '.') continue;
            int cnt = 0;
            int dir = 0;
            for(int d=0; d<4; d++){
                int ny = y + moveY[d];
                int nx = x + moveX[d];
                if (check_outside(ny, nx)) continue;
                if (map[ny][nx] == '#') {
                    cnt++;
                    dir = d;
                }
                if (cnt >= 2) break;
            }
            if (cnt == 1){
                vector<vector<bool> > visited(25, vector<bool>(25, false));
                visited[y][x] = true;
                dfs(y+1, x+1, y, x, dir, 1, "", visited);
            }
        }
    }
}

int main(int argc, char** argv){
    cin>>sizeY>>sizeX;
    for(int y=0; y<sizeY; y++){
        cin>>map[y];
        for(int x=0; x<sizeX; x++){
            if (map[y][x] == '#') goal_cnt++;
        }
    }
    find_start();
    cout<<answer;
}