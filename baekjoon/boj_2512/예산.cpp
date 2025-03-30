#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int main() {
    int answer = 0;
    int region_cnt; cin>>region_cnt;
    vector<int> budgets;
    for(int i=0; i<region_cnt; i++) {
        int budget; cin>>budget;
        budgets.push_back(budget);
    }
    int limit; cin>>limit;
    if (accumulate(budgets.begin(), budgets.end(), 0) <= limit) {
        // 요구한 양을 전체 예산 안에서 제공 가능
        cout<<*max_element(budgets.begin(), budgets.end());
        return 0;
    }
    sort(budgets.begin(), budgets.end());
    int left = 1, right = budgets.back();
    while(left <= right) {
        int mid = (left + right) / 2;
        int sum = 0;
        int max_value = 0;
        for(int i=0; i<budgets.size(); i++) {
            int real_budget = min(budgets[i], mid);
            sum += real_budget;
            max_value = max(max_value, real_budget);
        }
        if (sum <= limit) {
            // 전체 예산 안에 분배가 가능
            answer = max(answer, max_value);
            left = mid + 1;
        } else right = mid - 1;
    }
    cout<<answer;
}