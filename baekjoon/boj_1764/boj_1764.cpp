/**
 * @file boj_1764.cpp
 * @brief 백준 silver4 듣보잡
 * @version 0.1
 * @date 2024-08-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int main(){
    int cnt1, cnt2; cin>>cnt1>>cnt2;
    set<string> cant_see;
    set<string> result;
    for(int i=0; i<cnt1; i++) {
        string name; cin>>name;
        cant_see.insert(name);
    }
    for(int i=0; i<cnt2; i++) {
        string name; cin>>name;
        if (cant_see.find(name) != cant_see.end()) {
            result.insert(name);
        }
    }
    cout<<result.size()<<"\n";
    for(auto name : result) cout<<name<<"\n";
}