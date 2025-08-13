#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void print_maps(vector<string>& maps) {
    for(int y=0; y<maps.size(); y++) {
        for(int x=0; x<maps[y].size(); x++) {
            cout<<maps[y][x]<<' ';
        }
        cout<<"\n";
    }
}

bool solve(vector<string>& maps) {
    int x_cnt = 0, o_cnt = 0;
    bool x_win = false, o_win = false;

    // 1) 개수 세기
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            if (maps[y][x] == 'O') o_cnt++;
            else if (maps[y][x] == 'X') x_cnt++;
        }
    }

    // 2) 기본 카운트 제약
    if (!(x_cnt == o_cnt || x_cnt == o_cnt + 1)) return false; // X가 먼저 시작

    // 3) 승리 여부
    for (int y = 0; y < 3; y++) {
        int cx = 0, co = 0;
        for (int x = 0; x < 3; x++) {
            cx += (maps[y][x] == 'X');
            co += (maps[y][x] == 'O');
        }
        if (cx == 3) x_win = true;
        if (co == 3) o_win = true;
    }
    for (int x = 0; x < 3; x++) {
        int cx = 0, co = 0;
        for (int y = 0; y < 3; y++) {
            cx += (maps[y][x] == 'X');
            co += (maps[y][x] == 'O');
        }
        if (cx == 3) x_win = true;
        if (co == 3) o_win = true;
    }
    if (maps[0][0] == maps[1][1] && maps[1][1] == maps[2][2]) {
        if (maps[1][1] == 'X') x_win = true;
        if (maps[1][1] == 'O') o_win = true;
    }
    if (maps[0][2] == maps[1][1] && maps[1][1] == maps[2][0]) {
        if (maps[1][1] == 'X') x_win = true;
        if (maps[1][1] == 'O') o_win = true;
    }

    // 4) 양쪽 동시 승리 불가
    if (x_win && o_win) return false;

    // 5) 승자가 있는 경우: 마지막 수의 주인과 개수 일치
    if (x_win) return x_cnt == o_cnt + 1; // X가 이겼으면 X가 하나 더
    if (o_win) return x_cnt == o_cnt;     // O가 이겼으면 개수 같아야 함

    // 6) 승자가 없는 경우: 무승부 최종 상태여야 함(판이 꽉 참)
    return (x_cnt + o_cnt == 9) && (x_cnt == o_cnt + 1); // X=5, O=4
}


int main() {
    while(1) {
        string s; cin>>s;
        if (s == "end") break;
        vector<string> maps;
        maps.push_back(s.substr(0, 3));
        maps.push_back(s.substr(3, 3));
        maps.push_back(s.substr(6, 3));

        cout<<((solve(maps)) ? "valid\n" : "invalid\n");
    }
}