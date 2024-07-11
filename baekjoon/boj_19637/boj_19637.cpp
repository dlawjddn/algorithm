/**
 * @file boj_19637.cpp
 * @brief 백준 silver3 IF문 좀 누가 대신 써줘
 * @version 0.1
 * @date 2024-07-10
 * 
 * @copyright Copyright (c) 2024
 * 
 * map.. 제대로 공부 해야겠당..
 * 
 */
#include <iostream>
#include <vector>
#include <map>

using namespace std;

int grade, score;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin>>grade>>score;
    map<int, string> m;
    for(int i=0; i<grade; i++) {
        string s; cin>>s;
        int num; cin>>num;
        m.insert(make_pair(num, s));
    }
    for(int i=0; i<score; i++) {
        int num; cin>>num;
        cout<<(m.lower_bound(num) -> second)<<"\n";
    }
}