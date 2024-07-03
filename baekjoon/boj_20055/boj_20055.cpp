#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int half_len = 0, stop_cnt = 0;
vector<int> health;
vector<bool> exist;
queue<int> q;

void print_health(){
    for(auto h : health) {
        cout<<h<<" ";
    }
    cout<<"\n";
}

void print_exist(){
    cout<<"exist: ";
    for(int i=0; i<exist.size(); i++) {
        if (exist[i]) cout<<i<<" ";
    }
    cout<<"\n";
}

void rotate_belt(){
    vector<int> after_rotate(health.size(),0);
    vector<bool> next_exist(exist.size(), false);
    
    for(int i=0; i<health.size()-1; i++) {
        after_rotate[i+1] = health[i];
    } after_rotate[0] = health[health.size() - 1];
    health = after_rotate;

    for(int i=exist.size() - 1; i>=0; i--) {
        if (!exist[i]) continue;
        int npos = i + 1;
        if (npos == half_len - 1) {
            exist[i] = false;
            continue;
        } else {
            exist[i] = false, exist[i+1] = true;
        }

    }
}

void move_robot() {
    for (int i = half_len - 2; i >= 0; i--) {
        if (exist[i] && !exist[i + 1] && health[i + 1] > 0) {
            exist[i] = false;
            exist[i + 1] = true;
            health[i + 1]--;
        }
    }
    // 내리는 위치에 있는 로봇은 즉시 내린다.
    if (exist[half_len - 1]) {
        exist[half_len - 1] = false;
    }
}

void add_robot() {
    if (health[0] > 0 && !exist[0]) {
        health[0] -= 1;
        exist[0] = true;
    }
}

bool is_finish() {
    int cnt = 0;
    for(int i=0; i<health.size(); i++) {
        if (health[i] <= 0) cnt++;
        if (cnt >= stop_cnt) return true;
    }
    return false;
}

int main(){
    cin>>half_len>>stop_cnt;
    health.resize(2*half_len, 0);
    exist.resize(2*half_len, false);
    for(int i=0; i<2*half_len; i++) {
        cin>>health[i];
    }
    int cnt = 0;
    while(1) {
        ++cnt;
        //if (cnt >= 100) break;
        cout<<"turn "<<cnt<<"   ";
        rotate_belt();
        //cout<<"\nrotate, "; print_exist();
        move_robot();
        //cout<<"move, "; print_exist();
        add_robot();
        print_health();
        //print_exist();
        if (is_finish()) break;
    }
    cout<<cnt;
}