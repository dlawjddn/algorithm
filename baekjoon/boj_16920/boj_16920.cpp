/**
 * @file boj_16920.cpp
 * @brief 백준 gold2 확장게임
 * @version 0.1
 * @date 2024-07-06
 * 
 * @copyright Copyright (c) 2024
 * 
 * 벽 느꼈다 ㄹㅇ..
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int sizeY, sizeX, player_cnt, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<int> answer;
vector<int> move_size;
vector<string> maps;
vector<vector<int> > result;
vector<vector<pair<int, int> > > players;

bool check_outside(int y, int x) {
    return y < 0 || y >= sizeY || x < 0 || x >= sizeX;
}


int main(){
    cin>>sizeY>>sizeX>>player_cnt;
    answer.resize(player_cnt + 1, 0);
    move_size.resize(player_cnt + 1, 0);
    maps.resize(sizeY);
    result.resize(sizeY, vector<int>(sizeX, 0));
    players.resize(player_cnt + 1, vector<pair<int, int> >());
    for(int i=1; i<=player_cnt; i++) cin>>move_size[i];
    for(int y=0; y<sizeY; y++) {
        cin>>maps[y];
        for(int x=0; x<sizeX; x++) {
            if (maps[y][x] >= '1' && maps[y][x] <= '9') {
                int player = maps[y][x] - '0';
                players[player].push_back(make_pair(y, x));
                result[y][x] = player;
            }
        }
    }

    while(1) {
        bool end = true;
        for(int player=1; player<=player_cnt; player++) {
            for(int step = 0; step<move_size[player]; step++) {
                bool stop = true;
                vector<pair<int, int> > next;
                for(auto pos : players[player]) {
                    int y = pos.first;
                    int x = pos.second;
                    for(int d=0; d<4; d++) {
                        int ny = y + moveY[d];
                        int nx = x + moveX[d];
                        if (check_outside(ny, nx) || maps[ny][nx] != '.') continue;
                        stop = false;
                        end = false;
                        next.push_back(make_pair(ny, nx));
                        maps[ny][nx] = player + '0';
                        result[ny][nx] = player;
                    }
                }
                if (stop) break;
                players[player] = next;
            }
        }
        if (end) break;
    }

    for(int y=0; y<sizeY; y++) {
        for(int x=0; x<sizeX; x++) {
            if (result[y][x] >= 1 && result[y][x] <= player_cnt) {
                answer[result[y][x]]++;
            }
        }
    }
    for(int i=1; i<=player_cnt; i++) cout<<answer[i]<<" ";
}