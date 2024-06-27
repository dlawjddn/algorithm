/**
 * @file boj_17780.cpp
 * @brief 백준 gold2 새로운게임
 * @version 0.1
 * @date 2024-06-27
 * 
 * @copyright Copyright (c) 2024
 * 
 * 문제 조건을 잘 파악하지 못해서 풀지 못했음.. 더 잘 파악하자
 * 
 * 구현문제를 풀 때
 * 1. 내가 바꾸지말자.. 문제 그대로 구현하기
 * 2. 구현의 경우에는 시간 복잡도 고려 덜하기 -> 웬만하면 그냥 풀림
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Unit{
    int y, x, dir;
    bool is_under;
};
vector<vector<int> > board(13, vector<int>(13, 0));
vector<vector<vector<int> > > maps(13, vector<vector<int> >(13));
vector<Unit> units;
int sq_size = 0, unit_cnt = 0, moveY[5]={0,0,0,-1,1}, moveX[5]={0,1,-1,0,0};

Unit make_unit(int y, int x, int dir, bool is_under) {
    Unit unit;
    unit.y = y;
    unit.x = x;
    unit.dir = dir;
    unit.is_under = is_under;
    return unit;
}

void print_units(){
    for(int i=1; i<=unit_cnt; i++) {
        cout<<units[i].y<<" "<<units[i].x<<" "<<units[i].dir<<" "<<units[i].is_under<<"\n";
    }
}

void print_maps(){
    for(int y=1; y<=sq_size; y++) {
        for(int x=1; x<=sq_size; x++) {
            cout<<maps[y][x].size()<<" ";
        }
        cout<<"\n";
    }
}

bool check_outside(int y, int x) {
    return y <= 0 || y > sq_size || x <= 0 || x > sq_size;
}

bool is_finish() {
    for(int y=1; y<=sq_size; y++) {
        for(int x=1; x<=sq_size; x++) {
            if (maps[y][x].size() >= 4)
                return true; 
        }
    }
    return false;
}

void move_unit(int y, int x, int ny, int nx, vector<int> units_idx, bool is_red){
    // 현재 위치 -> 다음 위치로 변경
    for (auto unit_idx : units_idx) {
        units[unit_idx].y = ny;
        units[unit_idx].x = nx;
    }
    // 반대 위치에 유닛 인덱스 추가하기

    // 빨간색
    if (is_red)
        maps[ny][nx].insert(maps[ny][nx].end(), maps[y][x].rbegin(), maps[y][x].rend());
    // 흰색
    else
        maps[ny][nx].insert(maps[ny][nx].end(), maps[y][x].begin(), maps[y][x].end());
    // 기존 유닛들 옮겼으니 지우기
    maps[y][x].clear();

    // 밑 여부 초기화해주기
    for(auto unit_idx : maps[ny][nx]) units[unit_idx].is_under = false;
    // 맨 밑 유닛 체크
    int under_unit_idx = maps[ny][nx][0];
    units[under_unit_idx].is_under = true;
}


int solution() {
    int turn = 0;
    while(turn < 1000) {
        ++turn;
        //cout<<"turn: "<<turn<<"\n";
        for(int i=1; i<=units.size(); i++) {
            Unit unit = units[i];
            // 밑에 있는 유닛이 아니라면 제외
            if (!unit.is_under) continue;

            // 현재 유닛의 위치와 방향 조회
            int y = unit.y;
            int x = unit.x;
            int d = unit.dir;
            // 현재 위치에 존재하는 유닛들
            vector<int> now_units_idx = maps[y][x];

            // 현재 유닛의 다음 위치
            int ny = y + moveY[d];
            int nx = x + moveX[d];


            // 다음 위치가 격자 밖이거나 파란색인 경우
            if (check_outside(ny, nx) || board[ny][nx] == 2) {
                // 반대 방향에 대한 위치와 방향
                int other_d = (d % 2 == 0) ? d-1 : d+1;
                int oy = y + moveY[other_d];
                int ox = x + moveX[other_d];

                // 방향 바꿔주기
                units[i].dir = other_d;

                // 반대 방향도 격자 밖이거나 파란색임
                if (check_outside(oy, ox) || board[oy][ox] == 2) {
                    continue;
                }
                // 반대 방향이 빨간색임
                else if (board[oy][ox] == 1) move_unit(y, x, oy, ox, now_units_idx, true);
                // 반대 방향이 흰색임
                else if (board[oy][ox] == 0) move_unit(y, x, oy, ox, now_units_idx, false);
            }
            // 다음 위치가 빨간색인 경우
            else if (board[ny][nx] == 1) move_unit(y, x, ny, nx, now_units_idx, true);
            // 다음 위치가 흰색인 경우
            else if (board[ny][nx] == 0) move_unit(y, x, ny, nx, now_units_idx, false);
        }
        // print_units();
        // cout<<"\n";
        // print_maps();
        if (is_finish()) return turn;
    }
    return -1;
}

int main(){
    cin>>sq_size>>unit_cnt;
    for(int y=1; y<=sq_size; y++) {
        for(int x=1; x<=sq_size; x++) {
            cin>>board[y][x];
        }
    }
    units.resize(unit_cnt+1);
    for(int i=1; i<=unit_cnt; i++) {
        int y; cin>>y;
        int x; cin>>x;
        int dir; cin>>dir;
        units[i] = make_unit(y, x, dir, true);
        maps[y][x].push_back(i);
    }
    cout<<solution();
}