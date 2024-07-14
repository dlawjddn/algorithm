/**
 * @file boj_25757.cpp
 * @brief 백준 silver5 임스와 함께하는 미니게임
 * @version 0.1
 * @date 2024-07-14
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <set>

using namespace std;

int people_cnt;
char game;
set<string> s;
int cnt_player() {
    if (game == 'Y') return 1;
    else if (game == 'F') return 2;
    return 3;
}

int main(){
    cin>>people_cnt>>game;
    for(int i=0; i<people_cnt; i++) {
        string name; cin>>name;
        s.insert(name);
    }
    cout<<s.size() / cnt_player();
}