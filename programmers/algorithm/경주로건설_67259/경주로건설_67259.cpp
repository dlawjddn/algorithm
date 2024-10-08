/**
 * @file 경주로건설_67259.cpp
 * @brief 프로그래머스 lv3. 경주로 건설
 * @version 0.1
 * @date 2024-06-20
 * 
 * @copyright Copyright (c) 2024
 * 
 * 오답 코드를 보면 알겠지만, 3차원 방문배열이 아닌 2차원 방문배열을 사용하여 오답이 발생했다.
 * 반드시 기억해야겠다..
 * 3차원 방문 배열을 사용해야 하는 경우 -> 방향에 따라서 값이 달라지는 경우: 방향에 따른 최소값을 알아야함
 * 2차원 방문 배열을 사용해야 하는 경우 -> 방향은 큰 영향이 없음: 단지 그냥 특정 위치에서 이동할 수 있는 경우를 나타냄
 * 
 * 오답 코드를 기준으로 최소값만 판별하는 if (visited[now.y][now.x][now.d] != now.cost) continue; 이 코드에서 오류가 발생했다.
 * 방문에 따른 최소값이 아닌 위치에 대한 최소값을 고려했기 때문이다.
 * 
 * 근데 사실 아직도 이해가 안 되긴 한다.. 왜 3차원을 써야하지가 아닌 왜 2차원이 안될까 싶은 부분이다..
 */
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

struct Info{
    int y, x, d, cost;
    
    bool operator<(const Info &other) const {
        return cost > other.cost;
    }
};
int moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<vector<vector<int> > > visited(25, vector<vector<int> >(25, vector<int>(4, 987654321)));

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
    if (now.d == -1 || now.d == d)
        return now.cost + 100;
    else
        return now.cost + 600;
}

void bfs(vector<vector<int> > board, int sq_size) {
    priority_queue<Info> pq;
    pq.push(make_info(0, 0, -1, 0));
    while(!pq.empty()){
        Info now = pq.top(); pq.pop();
        if (visited[now.y][now.x][now.d] != now.cost) continue;
        for(int d=0; d<4; d++){
            int ny = now.y + moveY[d];
            int nx = now.x + moveX[d];
            if (check_outside(ny, nx, sq_size) || board[ny][nx] == 1) continue;
            int ncost = get_ncost(now, d);
            if (ncost > visited[ny][nx][d]) continue;
            pq.push(make_info(ny, nx, d, ncost));
            visited[ny][nx][d] = ncost;
        }
    }
}

int solution(vector<vector<int>> board) {
    int answer = 0;
    int sq_size = board.size();
    bfs(board, sq_size);
    // for(int y=0; y<board.size(); y++){
    //     for(int x=0; x<board.size(); x++){
    //         cout<<*min_element(visited[y][x].begin(), visited[y][x].end())<<" ";
    //     }
    //     cout<<"\n";
    // }
    return *min_element(visited[sq_size-1][sq_size-1].begin(), visited[sq_size-1][sq_size-1].end());
}
/**
 * @file 경주로건설_67259.cpp
 * @brief 프로그래머스 lv.3 경주로 건설
 * @version 0.1
 * @date 2024-08-19
 * 
 * @copyright Copyright (c) 2024
 * 
 * 키야~ 약 두달전에 못 푼 문제를 풀었다 ㅋㅋ 야호~
 * 정우야 모르면 외워~ 방향에 따라 갈 수 있는 경우의 수가 나뉘잖아 ㅋㅋ
 * 
 */
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

#define INF 987654321

using namespace std;

struct Info {
    int y, x, dir, move_cnt, dir_cnt, total_cost;
    bool operator<(Info other) const {
        return total_cost > other.total_cost;
    }
};
int sizeY = 0, sizeX = 0, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<vector<vector<int> > > visited;

Info make_info(int y, int x, int dir, int move_cnt, int dir_cnt, int total_cost) {
    Info info;
    info.y = y;
    info.x = x;
    info.dir = dir;
    info.move_cnt = move_cnt;
    info.dir_cnt = dir_cnt;
    info.total_cost = total_cost;
    return info;
}

bool check_outside(int y, int x) {
    return y < 0 || y >= sizeY || x < 0 || x >= sizeX;
}

int dijkstra(vector<vector<int>>& board) {
    priority_queue<Info> pq;
    for(int d=0; d<4; d++) {
        pq.push(make_info(0,0,d, 0,0,0));
        visited[0][0][d] = 0;
    }
    while(!pq.empty()) {
        auto[y, x, dir, move_cnt, dir_cnt, total_cost] = pq.top(); pq.pop();
        if (visited[y][x][dir] != total_cost) continue;
        for(int d=0; d<4; d++) {
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            int ndir = d;
            int nmove_cnt = move_cnt + 1;
            int ndir_cnt = (dir == ndir) ? dir_cnt : dir_cnt + 1;
            int ntotal_cost = nmove_cnt * 100 + ndir_cnt * 500;
            if (check_outside(ny, nx) || board[ny][nx] == 1) continue;
            if (visited[ny][nx][ndir] <= ntotal_cost) continue;
            pq.push(make_info(ny, nx, ndir, nmove_cnt, ndir_cnt, ntotal_cost));
            visited[ny][nx][ndir] = ntotal_cost;
        }
    }
    return *min_element(visited[sizeY-1][sizeX-1].begin(), visited[sizeY-1][sizeX-1].end());
}

int solution(vector<vector<int>> board) {
    sizeY = board.size(), sizeX = board[0].size();
    visited.resize(sizeY, vector<vector<int> >(sizeX, vector<int>(4, INF)));
    return dijkstra(board);
}