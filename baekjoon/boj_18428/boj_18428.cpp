/**
 * @file boj_18428.cpp
 * @brief 백준 gold5 감시 피하기
 * @version 0.1
 * @date 2024-06-30
 * 
 * @copyright Copyright (c) 2024
 * 
 * 오랜만에 원트~!
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool cant_find = false;
int sq_size = 0, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<vector<char> > maps;
vector<pair<int, int> > teachers;
vector<pair<int, int> > blanks;
vector<bool> chosen;

void print_vector(vector<int> choose) {
    for(auto c : choose) {
        cout<<c<<" ";
    }
    cout<<"\n";
}

void print_maps(){
    for(int y=0; y<sq_size; y++) {
        for(int x=0; x<sq_size; x++) {
            cout<<maps[y][x]<<" ";
        }
        cout<<"\n";
    }
}

bool check_outside(int y, int x) {
    return y < 0 || y >= sq_size || x < 0 || x >= sq_size;
}

void change_maps(char c, vector<int> choose) {
    for(auto idx : choose) {
        maps[blanks[idx].first][blanks[idx].second] = c;
    }
}

bool check_find(vector<int> choose) {
    change_maps('O', choose);
    for(auto teacher : teachers) {
        int y = teacher.first;
        int x = teacher.second;
        for(int d=0; d<4; d++) {
            int cnt = 0;
            while(1) {
                ++cnt;
                int ny = y + (cnt * moveY[d]);
                int nx = x + (cnt * moveX[d]);
                if (check_outside(ny, nx)) break;
                if (maps[ny][nx] == 'S') {
                    change_maps('X', choose);
                    return false;
                }
                else if (maps[ny][nx] == 'O') break;
            }
        }
    }
    return true;
}

void dfs(int idx, vector<int> choose) {
    // 3개를 골랐을 때
    if (choose.size() == 3) {
        //print_vector(choose);
        if (check_find(choose)) {
            cant_find = true;
            //cout<<"YES\n";
            return ;
        }
        //else cout<<"NO\n";
        return ;
    }

    // 선택
    for(int i=idx; i<blanks.size(); i++) {
        if (chosen[i]) continue;
        choose.push_back(i);
        chosen[i] = true;
        dfs(i, choose);
        if (cant_find) return ;
        choose.erase(choose.end() - 1);
        chosen[i] = false;
    }
}

int main(){
    cin>>sq_size;
    maps.resize(sq_size, vector<char>(sq_size));
    for(int y=0; y<sq_size; y++) {
        for(int x=0; x<sq_size; x++) {
            cin>>maps[y][x];
            if (maps[y][x] == 'X') {
                blanks.push_back(make_pair(y, x));
            }
            else if (maps[y][x] == 'T') {
                teachers.push_back(make_pair(y, x));
            }
        }
    }
    chosen.resize(blanks.size());
    vector<int> start;
    dfs(0, start);
    if (cant_find) cout<<"YES";
    else cout<<"NO";
    //print_maps();
}