/**
 * @file boj_28278.cpp
 * @brief 백준 silver4 스택2
 * @version 0.1
 * @date 2024-07-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <stack>

using namespace std;

int order_cnt;
stack<int> s;

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>order_cnt;
    for(int i=0; i<order_cnt; i++) {
        int order; cin>>order;
        if (order == 1) {
            int num; cin>>num;
            s.push(num);
        } else if (order == 2) {
            if (s.empty()) {
                cout<<"-1\n";
            } else {
                cout<<s.top()<<"\n";s.pop();
            }
        } else if (order == 3) {
            cout<<s.size()<<"\n";
        } else if (order == 4) {
            if (s.empty()) {
                cout<<"1\n";
            } else {
                cout<<"0\n";
            }
        } else {
            if (s.empty()) {
                cout<<"-1\n";
            } else {
                cout<<s.top()<<"\n";
            }
        }
    }
}