#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

unordered_map<string, int> origin;

int solution(vector<string> want, vector<int> number, vector<string> discount) {
    int answer = 0;
    for(int i=0; i<want.size(); i++) {
        origin[want[i]] = number[i];
    }
    for(int i=0; i<= discount.size() - 10; i++) {
        unordered_map<string, int> temp = origin;
        for(int j=0; j<10; j++) {
            temp[discount[i+j]] -= 1;
        }
        vector<pair<string, int> > check(temp.begin(), temp.end());
        bool success = true;
        for(int i=0; i<check.size(); i++) {
            if (check[i].second != 0) {
                success = false;
                break;
            }
        }
        if (success) answer++;
    }
    return answer;
}