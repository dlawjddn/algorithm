/**
 * @file 미로탈출명령어_150265.cpp
 * @brief 프로그래머스 lv3. 미로 탈출 명령어
 * @version 0.1
 * @date 2024-06-20
 * 
 * @copyright Copyright (c) 2024
 * 
 * 흠.. 이것도 역시 방향에 따른 방문처리가 중요했던 문제이다.. 어제 분명 dfs를 이용한 그래프 문제에서 방문처리를 다루는 방법에 대해 정리했던 거 같은데..
 * 아직 완벽하게 내 머리에 들어오지 않았나보다.. ㅠ
 * 
 * 이 문제의 특징은 시작점에서 도착점으로 제시된 움직임만큼 움직이는 경우들 중에 사전순으로 가장 빠른 경로 하나를 선택하는 것이다.
 * 이 부분에서 음.. 나는 굳이라고 생각하긴 했지만 그리디처럼 움직이는 방향을 dfs 순회의 기준으로 둬서 첫번째로 오는 경로가 사전순으로 제일 빠른 경로를 보장하면 된다..
 * 솔직히 나는 굳이라고 생각하긴 하는데 이렇게 하면 빠르긴 빠를 것 같다
 * 
 * 이번 3차원 방문배열의 특징은 50*50 사이즈의 이차원 배열을 3차원으로 확장하면서 이 3차원 배열의 값을 어떻게 지정하냐가 고민이었다.
 * 동서남북 4방향으로 해야할까 싶었지만 50*50에서 아무리 많이 움직여도 2500번이라는 생각으로 2501의 사이즈를 갖고 각 움직인 횟수를 하는 것이 맞아 보였다..
 * 
 * 너무 아쉽다 한번에 정답 보지 않고 풀 수 있는 문제 같은데 아직은 숙련이 더 필요한 것 같다
 * 
 */
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int moveY[4]={1, 0, 0, -1}, moveX[4]={0, -1, 1, 0};
string answer = "z";
vector<vector<vector<bool> > > visited(50, vector<vector<bool> >(50, vector<bool>(2501, false)));

bool check_outside(int y, int x, int sizeY, int sizeX){
    return y < 0 || y >= sizeY || x < 0 || x >= sizeX;
}

char get_ndir(int d){
    if (d == 0)
        return 'd';
    else if (d == 1)
        return 'l';
    else if (d == 2)
        return 'r';
    else
        return 'u';
}

void dfs(int sizeY, int sizeX, int y, int x, int goalY, int goalX, int limit, string route) {
    visited[y][x][route.size()] = true;
    if (route.size() == limit && goalY == y && goalX == x){
        //cout<<route<<"\n";
        if (answer > route) {
            answer = route;
            return ;
        }
    }
    if (route.size() >= limit)
        return ;
    for(int d=0; d<4; d++){
        int ny = y + moveY[d];
        int nx = x + moveX[d];
        if (check_outside(ny, nx, sizeY, sizeX) || visited[ny][nx][route.size() + 1]) continue;
        dfs(sizeY, sizeX, ny, nx, goalY, goalX, limit, route + get_ndir(d));
    }
}
string solution(int n, int m, int x, int y, int r, int c, int k) {
    dfs(n, m, x-1, y-1, r-1, c-1, k, "");
    if (answer == "z")
        return "impossible";
    return answer;
}