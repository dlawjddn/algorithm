/**
 * @file boj_5430.cpp
 * @brief 백준 gold5 AC
 * @version 0.1
 * @date 2024-07-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

deque<int> dq;

void convert_number(string arr) {
    int num = 0;
    deque<int> temp_dq;
    for(int i=0; i<arr.size(); i++) {
        if (arr[i] == '[') continue;
        else if (arr[i] == ']') {
            if (num == 0) continue;
            temp_dq.push_back(num);
        }
        else if (arr[i] == ',') {
            temp_dq.push_back(num);
            num = 0;
            continue;
        }
        num = (num * 10) + arr[i] - '0';
    }
    dq = temp_dq;
}
int main(){
    int test_case; cin>>test_case;
    for(int t=0; t<test_case; t++) {
        string order; cin>>order;
        int len; cin>>len;
        string arr; cin>>arr;
        convert_number(arr);
        bool reverse = false, stop = false;
        for(int i=0; i<order.size(); i++) {
            if (order[i] == 'R') reverse = ((reverse) ? false : true);
            else {
                if (dq.empty()) {
                    cout<<"error\n";
                    stop = true;
                    break;
                }
                (reverse) ? dq.pop_back() : dq.pop_front();
            }
        }
        if (stop) continue;
        cout<<"[";
        while(!dq.empty()) {
            if (reverse) {
                cout<<dq.back(); dq.pop_back();
                if(!dq.empty()) cout<<",";
            }
            else {
                cout<<dq.front(); dq.pop_front();
                if(!dq.empty()) cout<<",";
            }
        }
        cout<<"]\n";
    }
}