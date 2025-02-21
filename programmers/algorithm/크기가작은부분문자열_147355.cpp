#include <string>
#include <vector>

using namespace std;

int solution(string t, string p) {
    int answer = 0;
    long long target = stoll(p);
    for(int i=0; i<= t.size() - p.size(); i++) {
        long long num = stoll(t.substr(i, p.size()));
        if (num <= target) answer++;
    }
    return answer;
}