#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

struct Info {
    int y, x, d, cost;
    
    bool operator<(const Info &other) const {
        return cost > other.cost;
    }
};

int moveY[4]={0,0,1,-1}, moveX[4]={1,-1,0,0};
vector<vector<int>> visited(25, vector<int>(25, 987654321));

void print_visited(int sq_size){
    for(int y=0; y<sq_size; y++){
        for(int x=0; x<sq_size; x++){
            if (visited[y][x] == 987654321)
                cout<<"0 ";
            else 
                cout << visited[y][x] << " ";
        }
        cout << "\n";
    }
}

Info make_info(int y, int x, int d, int cost){
    Info info;
    info.y = y;
    info.x = x;
    info.d = d;
    info.cost = cost;
    return info;
}

bool check_outside(int y, int x, int sq_size){
    return y < 0 || y >= sq_size || x < 0 || x >= sq_size;
}

int get_ncost(Info now, int d){
    if (now.d == d)
        return now.cost + 100;
    else
        return now.cost + 600;
}

void bfs(vector<vector<int>> board, int sq_size){
    priority_queue<Info> pq;
    visited[0][0] = 0;
    for (int d = 0; d < 4; d++) {
        int ny = moveY[d];
        int nx = moveX[d];
        if (!check_outside(ny, nx, sq_size) && board[ny][nx] == 0) {
            pq.push(make_info(ny, nx, d, 100));
            visited[ny][nx] = 100;
        }
    }

    while (!pq.empty()) {
        Info now = pq.top(); pq.pop();
        //if (visited[now.y][now.x] < now.cost) continue; -> 내가 틀린 이유
        for (int d = 0; d < 4; d++) {
            int ny = now.y + moveY[d];
            int nx = now.x + moveX[d];
            int nd = d;
            int ncost = get_ncost(now, d);
            if (check_outside(ny, nx, sq_size) || ncost > visited[ny][nx] || board[ny][nx] == 1) continue;
            pq.push(make_info(ny, nx, nd, ncost));
            visited[ny][nx] = ncost;
        }
    }
}

int solution(vector<vector<int>> board) {
    int answer = 0;
    bfs(board, board.size());
    //print_visited(board.size());
    return visited[board.size()-1][board.size()-1];
}
