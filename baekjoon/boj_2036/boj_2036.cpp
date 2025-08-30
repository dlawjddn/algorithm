#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int cnt;
priority_queue<int, vector<int>, less<int> > upper_zero; // 초과
priority_queue<int, vector<int>, greater<int> > lower_zero; // 0 이하

int main() {
    cin>>cnt;
    for(int i=0; i<cnt; i++) {
        int num; cin>>num;
        if (num > 0) upper_zero.push(num);
        else lower_zero.push(num);
    }

    long long answer = 0;
    while(!upper_zero.empty()) {
        int num1 = upper_zero.top(); upper_zero.pop();
        if (upper_zero.empty()) {
            answer += num1;
            continue;
        }
        int num2 = upper_zero.top(); upper_zero.pop();

        long long mul = 1LL * num1 * num2;
        long long sum = 1LL * num1 + num2;
        answer += (mul < sum ? sum : mul);
    }

    while(!lower_zero.empty()) {
        int num1 = lower_zero.top(); lower_zero.pop();
        if (lower_zero.empty()) {
            answer += num1;
            continue;
        }
        int num2 = lower_zero.top(); lower_zero.pop();

        long long mul = 1LL * num1 * num2;
        long long sum = 1LL * num1 + num2;
        answer += (mul < sum ? sum : mul);
    }
    cout<<answer;
}