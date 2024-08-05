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