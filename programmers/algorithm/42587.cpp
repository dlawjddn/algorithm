#include <string>
#include <algorithm>
#include <vector>


using namespace std;

// 프로세스
int solution(vector<int> priorities, int location) {
    int answer = 1;
    while(1){
        if (priorities[0] == *max_element(priorities.begin(), priorities.end())){
            priorities.erase(priorities.begin());
            if (location == 0){
                break;
            } else {
                location--;
            }
            answer++;
        } else {
            priorities.push_back(priorities[0]);
            priorities.erase(priorities.begin());
            if (location == 0) location = priorities.size()-1;
            else location--;
        }
    }
    return answer;
}