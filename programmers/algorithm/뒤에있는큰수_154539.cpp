#include <string>
#include <vector>
#include <stack>

using namespace std;

vector<int> solution(vector<int> numbers) {
    vector<int> answer(numbers.size(), -1);
    stack<int> s;
    for(int i=0; i<numbers.size(); i++) {
        while(!s.empty() && numbers[s.top()] < numbers[i]) {
            int idx = s.top(); s.pop();
            answer[idx] = numbers[i];
        }
        s.push(i);
    }
    return answer;
}
/**
 * @file 뒤에있는큰수_154539.cpp
 * @brief 프로그래머스 lv.2 뒤에 있는 큰 수
 * @version 0.1
 * @date 2024-09-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <stack>

using namespace std;

stack<int> s;

vector<int> solution(vector<int> numbers) {
    vector<int> answer(numbers.size(), -1);
    for(int i=0; i<numbers.size(); i++) {
        while(!s.empty() && numbers[s.top()] < numbers[i]) {
            int idx = s.top(); s.pop();
            answer[idx] = numbers[i];
        }
        s.push(i);
    }
    return answer;
}