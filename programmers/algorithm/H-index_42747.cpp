#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> citations) {
    int answer = 0;
    sort(citations.begin(), citations.end());
    int max_value = citations[citations.size() - 1];
    for(int i=max_value; i>=0; i--) {
        int upper = 0;
        for(int j=0; j<citations.size(); j++) {
            if (citations[j] >= i) upper += 1;
        }
        if (upper >= i) {
            answer = max(answer, i);
        }
    }
    return answer;
}