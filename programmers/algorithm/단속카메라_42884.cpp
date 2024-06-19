#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<vector<int>> routes) {
    int answer = 1;
    sort(routes.begin(), routes.end());
    int limit_time = routes[0][1];
    for(auto route : routes) {
        if (limit_time < route[0]) {
            answer++;
            limit_time = route[1];
        }
        if (limit_time > route[1])
            limit_time = route[1];
    }
    return answer;
}