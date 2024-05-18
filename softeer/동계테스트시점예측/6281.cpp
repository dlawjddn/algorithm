#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int sizeY=0, sizeX=0, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<vector<int> > map(100, vector<int>(100, 0));
vector<vector<int> > outside(100, vector<int>(100, 0));

void print_visited(){
    for(int y=0; y<sizeY; y++){
        for(int x=0; x<sizeX; x++){
            cout<<outside[y][x];
        }
        cout<<"\n";
    }
}

void print_map(){
    for(int y=0; y<sizeY; y++){
        for(int x=0; x<sizeX; x++){
            cout<<map[y][x];
        }
        cout<<"\n";
    }
}

bool check_bound(int y, int x){
    return y < 0 || y >= sizeY || x < 0 || x>= sizeX;
}

void check_outside(){
    queue<pair<int, int> > q;
    vector<vector<int> > visited(100, vector<int>(100, 0));
    visited[0][0] = 1;
    q.push(make_pair(0, 0));
    while(!q.empty()){
        int y = q.front().first;
        int x = q.front().second; q.pop();
        for(int d=0; d<4; d++){
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            if (check_bound(ny, nx) || visited[ny][nx] || map[ny][nx]) continue;
            q.push(make_pair(ny, nx));
            visited[ny][nx] += 1;
        }
    }
    outside = visited;
}

bool melting(){
    bool stop = true;
    for(int y=0; y<sizeY; y++){
        for(int x=0; x<sizeX; x++){
            if (map[y][x] == 1){
                int cnt = 0;
                for(int d=0; d<4; d++){
                    int ny = y + moveY[d];
                    int nx = x + moveX[d];
                    if (check_bound(ny, nx)) continue;
                    if (outside[ny][nx] == 1) cnt++;
                }
                if (cnt >= 2) {
                    map[y][x] -= 1;
                    stop = false;
                }
            }
        }
    }
    return stop;
}

int main(int argc, char** argv)
{
    cin>>sizeY>>sizeX;
    for(int y=0; y<sizeY; y++){
        for(int x=0; x<sizeX; x++){
            cin>>map[y][x];
        }
    }
    int answer = 0;
    while(1){
        check_outside();
        if (melting())
            break;
        answer += 1;
    }
    cout<<answer;
    // check_outside();
    // melting();
    // print_map();
}