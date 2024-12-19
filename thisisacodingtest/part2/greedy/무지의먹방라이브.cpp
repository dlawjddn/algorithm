#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <numeric>
#include <algorithm>

using namespace std;

priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;

bool compare(pair<int, int> p1, pair<int, int> p2) {
    return p1.second < p2.second;
}

int solution(vector<int> food_times, long long k) {
    int answer = 0;
    
    // 종료되는 시점 이전에 다 먹은 경우
    //long long sum = accumulate(food_times.begin(), food_times.end(), 0);
    // -> accumulate는 int 반환이라 효율성 테스트에서 틀림
    long long sum = 0;
    for(int i=0; i<food_times.size(); i++) {
        pq.push({food_times[i], i+1});
        sum += food_times[i];
    }
    if (sum <= k) return -1;
    
    long long food_cnt = food_times.size();
    long long pre_food_time = 0;
    long long total_time = 0;
    
    // 반복문의 조건문의 의미
    // 1. 종료까지의 시간(k) - 현재까지 소모한 시간(total_time) = 종료까지 남은 시간
    // 2. (현재 가장 작은 음식의 남은 양 - 이전까지 먹은 양) = 현재 남은 음식을 다 먹는데 걸리는 시간
    // 3. 현재 남은 음식을 다 먹는데 걸리는 시간 * 음식의 개수 -> 현재 남은 음식을 다 먹는데 걸리는 전체 사이클 시간
    
    // 이 반복문은 왜 쓰이는 것인가?
    // K까지의 시간까지 다 먹을 수 있는 음식을 시간이 작게 걸리는 음식부터 제거하고, 그때 마다 시간을 계산하기 위해서
    while(((pq.top().first - pre_food_time) * food_cnt) <= k - total_time) {
        auto[food_time, food_idx] = pq.top(); pq.pop();
        total_time += ((food_time - pre_food_time) * food_cnt);
        pre_food_time = food_time;
        food_cnt--;
    }
    
    vector<pair<int, int> > result;
    while(!pq.empty()) {
         result.push_back(pq.top()); pq.pop();
    }
    sort(result.begin(), result.end(), compare);
    
    return result[(k-total_time) % food_cnt].second;
}