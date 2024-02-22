#include <string>
#include <cstring>
#include <vector>

using namespace std;

// 기능개발
vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;
    int days[101];
    int day = -1;
    memset(days, 0, sizeof(days));
    for(int i=0; i<progresses.size(); i++){
        while(progresses[i] + day * speeds[i] < 100) day++;
        days[day]++;
    }
    for(int i=0; i<101; i++){
        if (days[i] != 0)
            answer.push_back(days[i]);
    }
    return answer;
}