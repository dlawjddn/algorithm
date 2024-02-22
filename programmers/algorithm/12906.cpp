#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>

using namespace std;

// 같은 숫자는 싫어
vector<int> solution(vector<int> arr)
{
    vector<int> answer;
    stack<int> s;
    s.push(arr[0]);
    for(int i=0; i<arr.size(); i++){
        if (s.top() == arr[i]) continue;
        else s.push(arr[i]);
    }
    int len = s.size();
    for(int i=0; i<len; i++){
        answer.push_back(s.top());
        s.pop();
    }
    reverse(answer.begin(), answer.end());
    return answer;
}