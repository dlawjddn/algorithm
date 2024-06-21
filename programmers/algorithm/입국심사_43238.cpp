/**
 * @file 입국심사_43238.cpp
 * @brief 프로그래머스 lv.3 입국심사
 * @version 0.1
 * @date 2024-06-21
 * 
 * @copyright Copyright (c) 2024
 * 
 * 이분탐색에 대해서 공부하기 위해서 공부를 진행하고 코드를 작성했다.
 * 
 * 이분 탐색은 정렬된 배열에서 처음과 끝을 기준으로 절반씩 범위를 바꿔가면서 탐색을 진행하는 것이다.
 * 아무리 큰 수가 나오더라도 2^n씩 줄어들기 때문에 굉장히 빠르게 찾을 수 있다 (최대값이 10인 1차원 배열의 경우 특정 수를 찾는데 약 30n의 시간복잡도로 수를 찾을 수 있다.)
 * 
 * 이론은 알고 있었는데 코드를 작성하는 법을 몰라서 공부하게 되었다.
 * 
 * 1. 이분탐색의 배열의 기준은 정답이 되는 기준이다. (ex. 최소 시간 -> 시간 배열)
 * 2. 이분탐색의 배열의 최소값과 최대값을 찾는다. (최소시간과 최대시간)
 * 3. 코드를 통해 최소와 최대의 중간값을 기준으로 문제의 조건을 찾는다.
 * 4. 최적의 답이 정답이 된다. (최소 시간을 구하는 문제 -> 가장 마지막의 시간이 최소 시간)
 * 
 * 이분탐색 문제를 더 열심히 풀어봐야겠다!
 * 
 */
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

long long solution(int n, vector<int> times) {
    long long answer = 0;
    sort(times.begin(), times.end());
    long long left = times[0];
    long long right = n * (long long)times[times.size()-1];
    
    while(left <= right){
        long long mid = (left + right) / 2;
        long long people_cnt = 0;
        for(auto time : times) {
            people_cnt += (mid / (long long) time);
        }
        if (people_cnt >= n) {
            right = mid - 1;
            answer = mid;
        }
        else {
            left = mid + 1;
        }
    }
    return answer;
}