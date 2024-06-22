#include <vector>
#include <numeric>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

int solution(vector<int> queue1, vector<int> queue2) {
    long long sum1 = accumulate(queue1.begin(), queue1.end(), 0LL);
    long long sum2 = accumulate(queue2.begin(), queue2.end(), 0LL);
    long long totalSum = sum1 + sum2;
    
    if (totalSum % 2 != 0) {
        return -1;
    }

    long long target = totalSum / 2;
    
    deque<int> q1(queue1.begin(), queue1.end());
    deque<int> q2(queue2.begin(), queue2.end());

    int answer = 0;
    int max_operations = queue1.size() + queue2.size() * 2;  

    while (sum1 != target && answer <= max_operations) {
        if (sum1 > target) {
            int num = q1.front();
            q1.pop_front();
            q2.push_back(num);
            sum1 -= num;
            sum2 += num;
        } else {
            int num = q2.front();
            q2.pop_front();
            q1.push_back(num);
            sum1 += num;
            sum2 -= num;
        }
        answer++;
    }

    return (sum1 == target) ? answer : -1;
}
