#include <set>
#include <string>
#include <vector>
#include <iostream>

using namespace std;
struct Info{
    int y, x;
    char dir;
    
    bool operator<(const Info& other) const {
        if (y != other.y) return y < other.y;
        if (x != other.x) return x < other.x;
        return dir < other.dir;
    }
};
set<Info> visited;

void print_visited(){
    for(auto visit : visited){
        cout<<visit.y<<" "<<visit.x<<" "<<visit.dir<<"\n";
    }
}

bool check_outside(int y, int x){
    return y < -5 || y > 5 || x < -5 || x > 5;
}

Info make_info(int y, int x, char dir){
    Info info;
    info.y = y;
    info.x = x;
    info.dir = dir;
    return info;
}

int move_person(string dirs){
    int y = 0, x = 0;
    for(auto dir : dirs){
        int ny = y , nx = x;
        char rdir;
        if (dir == 'U'){
            ny += 1;
            rdir = 'D';
        }
        else if (dir == 'D'){
            ny -= 1;
            rdir = 'U';
        }
        else if (dir == 'R'){
            nx += 1;
            rdir = 'L';
        }
        else {
            nx -= 1;
            rdir = 'R';
        }
        if (check_outside(ny, nx)) continue;
        visited.insert(make_info(y, x, dir));
        y = ny;
        x = nx;
        visited.insert(make_info(ny, nx, rdir));
    }
    //print_visited();
    return visited.size() / 2;
}
int solution(string dirs) {
    return move_person(dirs);
}
/**
 * @file 방문길이_49994.cpp
 * @brief 프로그래머스 lv.2 방문길이
 * @version 0.1
 * @date 2024-09-28
 * 
 * @copyright Copyright (c) 2024
 * 
 * 역방향 체크.. 가 중요했던 문제..
 * 
 * (1, 2) -> (2, 2)를 방문하게 되면,
 * (2, 2) -> (1, 2)도 방문하지 못함..
 * 
 * 이 역방향 체크를 해주지 못해서 틀림.. 좀 아쉽네
 * 
 */
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// 방향 이동 정의
int moveY[4] = {0, 1, 0, -1}; // 동, 남, 서, 북
int moveX[4] = {1, 0, -1, 0}; // 동, 남, 서, 북
vector<vector<vector<bool>>> visited(11, vector<vector<bool>>(11, vector<bool>(4, false)));
unordered_map<char, int> dir;

// 방향 초기화 함수
void init_dir() {
    dir['R'] = 0;
    dir['D'] = 1;
    dir['L'] = 2;
    dir['U'] = 3;
}

// 좌표가 범위를 벗어나는지 확인하는 함수
bool check_outside(int ny, int nx) {
    return ny < 0 || ny > 10 || nx < 0 || nx > 10;
}

int solution(string dirs) {
    int answer = 0;
    int y = 5, x = 5; // 시작 위치를 함수 내부에서 초기화
    init_dir(); // 방향 초기화

    for (auto d : dirs) {
        int ny = y + moveY[dir[d]];
        int nx = x + moveX[dir[d]];
        
        // 범위를 벗어나면 무시
        if (check_outside(ny, nx)) continue;

        // 양방향 경로 방문 체크
        if (!visited[y][x][dir[d]]) {
            answer++;
            // 현재 위치에서 다음 위치로의 방문 체크
            visited[y][x][dir[d]] = true;
            // 반대 방향 (다음 위치에서 현재 위치로) 방문 체크
            visited[ny][nx][(dir[d] + 2) % 4] = true;
        }
        
        // 현재 위치 갱신
        y = ny;
        x = nx;
    }
    return answer;
}
