#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int> > board(9, vector<int>(9, 0));
vector<vector<int> > answer;
vector<pair<int, int> > zeros;

vector<int> check(int sy, int sx) {
    vector<bool> exist(10, false);
    vector<int> result;
    //cout<<"pos: ("<<sy<<", "<<sx<<")  ";
    // 세로줄 확인
    for(int x=0; x<9; x++) {
        if (board[sy][x] == 0) continue;
        exist[board[sy][x]] = true;
    }

    // 가로줄 확인
    for(int y=0; y<9; y++) {
        if (board[y][sx] == 0) continue;
        exist[board[y][sx]] = true;
    }

    // 3*3 격자 확인
    int ssy = (sy / 3) * 3;
    int ssx = (sx / 3) * 3;
    for(int y = ssy; y < ssy + 3; y++) {
        for(int x = ssx; x < ssx + 3; x++) {
            if (board[y][x] == 0) continue;
            exist[board[y][x]] = true;
        }
    }
    for(int i=1; i<=9; i++) {
        if (exist[i]) continue;
        result.push_back(i);
    }
    return result;
}

void dfs(int idx) {
    if (idx == zeros.size()) {
        answer = board;
        return ; 
    }
    vector<int> possible = check(zeros[idx].first, zeros[idx].second);
    for(auto pos : possible) {
        board[zeros[idx].first][zeros[idx].second] = pos;
        dfs(idx + 1);
        board[zeros[idx].first][zeros[idx].second] = 0;
    }
}

int main(){
    for(int y=0; y<9; y++) {
        for(int x=0; x<9; x++) {
            cin>>board[y][x];
            if (board[y][x] == 0) zeros.push_back({y, x});
        }
    }
    dfs(0);
    for(int y=0; y<9; y++) {
        for(int x=0; x<9; x++) {
            cout<<answer[y][x]<<" ";
        }
        cout<<"\n";
    }
}