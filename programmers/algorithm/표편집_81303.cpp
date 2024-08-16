/**
 * @file 표편집_81303.cpp
 * @brief 프로그래머스 lv.3 2021 카카오 인턴십 표 편집
 * @version 0.1
 * @date 2024-08-16
 * 
 * @copyright Copyright (c) 2024
 * 
 * 전과 후의 부모를 벡터로 나타내서 for문 없이 찾는 방법이 신기했다. 이렇게도 하는구나..
 * 틀린 코드는 단순하게 for문으로 찾아버리니 시간초과가 발생했다.
 * 
 */
#include <string>
#include <vector>
#include <stack>

using namespace std;

stack<int> s;

string solution(int n, int k, vector<string> cmds) {
    string answer = string(n, 'O');
    vector<int> prev, next;
    prev.resize(n, -1);
    next.resize(n, -1);
    for(int i=0; i<n; i++) {
        prev[i] = i - 1;
        next[i] = i + 1;
    }
    next[n - 1] = -1;
    for(auto cmd : cmds) {
        if (cmd[0] == 'U') {
            int total_move = stoi(cmd.substr(2));
            while(total_move--) k = prev[k];
        }
        else if (cmd[0] == 'D') {
            int total_move = stoi(cmd.substr(2));
            while(total_move--) k = next[k];
        }
        else if (cmd[0] == 'C') {
            s.push(k);
            answer[k] = 'X';
            if (prev[k] != -1) next[prev[k]] = next[k];
            if (next[k] != -1) prev[next[k]] = prev[k];
            
            if (next[k] == -1) k = prev[k];
            else k = next[k];
        }
        else {
            int canceled = s.top(); s.pop();
            answer[canceled] = 'O';
            
            if (prev[canceled] != -1) next[prev[canceled]] = canceled;
            if (next[canceled] != -1) prev[next[canceled]] = canceled;
        }
    }
    return answer;
}

/*
#include <string>
#include <vector>
#include <iostream>
#include <stack>

using namespace std;

stack<int> s;

string solution(int n, int k, vector<string> cmds) {
    string answer = "";
    vector<bool> existed(n, true);
    for(auto cmd : cmds) {
        // 이동 하는 경우
        if (cmd[0] == 'U' || cmd[0] == 'D') {
            int total_cnt = stoi(cmd.substr(2));
            int cnt = 0;
            int dir = (cmd[0] == 'U') ? -1 : 1;
            int idx = k + dir;
            while(cnt < total_cnt) {
                if (existed[idx]) {
                    cnt++;
                }
                idx += dir;
            }
            k = idx - dir;
            //cout<<k<<"\n";
        }
        // 삭제 하는 경우
        else if (cmd[0] == 'C') {
            s.push(k);
            existed[k] = false;
            // k를 증가시키면서 현재 가리키는 위치를 찾음
            while(!existed[k] && k < n) {
                k++;
            }
            // 하지만 기존 k가 마지막 인덱스인 경우 끝까지 이동하게 됨
            if (!existed[k] || k >= n) {
               k -= 1;
                while(!existed[k]) {
                    k--;
               }
           }
            //cout<<k<<"\n";
        }
        // 삭제를 취소하는 경우
        else if (cmd[0] == 'Z') {
            existed[s.top()] = true;
            s.pop();
        }
    }
    for(int i=0; i<existed.size(); i++) {
        if (existed[i]) answer += 'O';
        else answer += 'X';
    }
    return answer;
}
*/