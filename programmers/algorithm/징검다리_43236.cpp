/**
 * @file 징검다리_43236.cpp
 * @brief 프로그래머스 lv.4  징검다리
 * @version 0.1
 * @date 2024-06-24
 * 
 * @copyright Copyright (c) 2024
 * 
 * 입국심사 문제에서 이분탐색을 공부하면서 이분탐색에 대해서 다시 한 번 공부하게 된 문제
 * 
 * 이분탐색 문제를 파악하는 방법
 * n과 같은 특정 수가 매우 크게 나옴 -> ex) 10억
 * 배열의 크기가 500,000처럼 한번 탐색은 가능하지만, n^2으로는 절대 못할 사이즈
 * 
 * 따라서 이분탐색 문제는 이분탐색으로 적절한 n을 찾고 그 n을 기준으로 큰 사이즈의 배열을 탐색하여 log n * n의 시간복잡도를 갖는 경우가 많다
 * 
 * 추가 꿀팁)
 * 이분탐색의 n은 이분탐색의 mid가 정답이 되는 문제가 대부분이다. 이 문제의 경우 0 ~ distance 범위를 이분 탐색으로 탐색하는데 이때 계산되는 mid는 각 돌 사이의 거리를 의미한다.
 * 따라서 이분탐색의 n은 정답을 찾는 것이고, 배열을 탐색하는 것은 이 n이 최적의 값이 맞는지 확인하는 과정이다. 
 * 
 */
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(int distance, vector<int> rocks, int n) {
    int answer = 0;
    rocks.push_back(distance);
    sort(rocks.begin(), rocks.end());
    int left = 0;
    int right = distance;
    while(left <= right) {
        int mid = (left + right) / 2;
        int prev = 0, cnt = 0;
        for(auto rock : rocks) {
            int diff = rock - prev;
            if (diff < mid) cnt++;
            else prev = rock;
        }
        if (cnt > n) {
            right = mid - 1;
        } else {
            left = mid + 1;
            answer = max(answer, mid);
        }
    }
    return answer;
}