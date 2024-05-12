/**
 * @file 7594.cpp
 * @author dlawjddn (dlawjddn0105@gmail.com)
 * @brief 소프티어 lv.3 나무 조경
 * @version 0.1
 * @date 2024-05-09
 * 
 * @copyright Copyright (c) 2024
 * 
 * 인접한 두개의 그룹을 묶는 방법에 대해서 고민이 된 문제
 * dfs를 쓰는건 알겠는데.. 이걸 어떻게 묶어야 하는지 고민..
 * 
 * 결국 정답을 봤고, 이렇게 하면 되는구나를 알게 됨! 비슷한 문제 나오면 풀 수 있을 듯!
 * 
 * 주의사항, 방향을 4방향으로 보면 시간초과가 발생함, 결국 중복되는 상황에 대해서 최적화가 필요함
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int> > map(4, vector<int>(4, 0));
vector<vector<bool> > visited(4, vector<bool>(4, false));
int moveY[2]={0,1}, moveX[2]={1,0}, sq_size = 0, answer = 0;

bool check_outside(int y, int x){
    // true: 범위 바깥
    // false: 범위 안
    return (y < 0 || y >= sq_size || x < 0  || x >= sq_size);
}

void change_visited(int y, int x, int ny, int nx, bool status){
    visited[y][x] = status;
    visited[ny][nx] = status;
}

void dfs(int max_cnt, int cnt, int sum){
    if (max_cnt == cnt){
        answer = max(answer, sum);
    }
    for(int y=0; y<sq_size; y++){
        for(int x=0; x<sq_size; x++){
            // 인접한 그룹은 해당 사항 없음 -> visited에 대해서 그룹으로 묶이는 순간 true로 변환되기 때문에 해줘야함
            if (visited[y][x]) continue;
            for(int d=0; d<2; d++){
                int ny = y + moveY[d];
                int nx = x + moveX[d];
                if (check_outside(ny, nx) || visited[ny][nx]) continue;
                change_visited(y, x, ny, nx, true);
                dfs(max_cnt, cnt+1, sum + map[y][x] + map[ny][nx]);
                change_visited(y, x, ny, nx, false);
            }
        }
    }
}

int main(int argc, char** argv)
{
    cin>>sq_size;
    for(int y=0; y<sq_size; y++){
        for(int x=0; x<sq_size; x++){
            cin>>map[y][x];
        }
    }
    int max_cnt = (sq_size == 2) ? 2 : 4;
    dfs(max_cnt, 0, 0);
    cout<<answer;
}