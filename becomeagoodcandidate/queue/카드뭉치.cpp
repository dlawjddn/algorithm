#include <string>
#include <vector>
#include <queue>

using namespace std;

queue<string> q1;
queue<string> q2;

string solution(vector<string> cards1, vector<string> cards2, vector<string> goal) {
    for(int i=0; i<cards1.size(); i++) q1.push(cards1[i]);
    for(int i=0; i<cards2.size(); i++) q2.push(cards2[i]);
    
    for(int i=0; i<goal.size(); i++) {
        if (goal[i] == q1.front()) {
            q1.pop();
            continue;
        }
        if (goal[i] == q2.front()) {
            q2.pop();
            continue;
        }
        return "No";
    }
    return "Yes";
}