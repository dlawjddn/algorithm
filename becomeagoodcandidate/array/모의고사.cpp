#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> answers) {
    vector<int> answer;
    vector<int> result(4, 0);
    vector<int> student1 = {1,2,3,4,5};
    vector<int> student2 = {2,1,2,3,2,4,2,5};
    vector<int> student3 = {3,3,1,1,2,2,4,4,5,5};
    
    for(int i=0; i<answers.size(); i++) {
        if (answers[i] == student1[i % student1.size()]) result[1]++;
        if (answers[i] == student2[i % student2.size()]) result[2]++;
        if (answers[i] == student3[i % student3.size()]) result[3]++;
    }
    int max_score = *max_element(result.begin(), result.end());
    for(int i=1; i<result.size(); i++) {
        if (max_score == result[i]) answer.push_back(i);
    }
    return answer;
}