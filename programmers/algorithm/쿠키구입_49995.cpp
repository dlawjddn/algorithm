/**
 * @file 쿠키구입_49995.cpp
 * @brief 프로그래머스 lv.4 쿠키 구입
 * @version 0.1
 * @date 2024-10-03
 * 
 * @copyright Copyright (c) 2024
 * 
 * 이게 레벨4까지의 문제는 아닌거 같긴 한데..
 * 
 * 근데 이 문제 너무 바보 같은 실수를 했다. 왼쪽과 오른쪽 따로 옮겨줘야하는데 동시에 옮겨서 한참을 헤맨 문제,,
 */
#include <string>
#include <vector>

using namespace std;

int limit;

bool check_outside(int left, int right) {
    return left < 0 || right >= limit;
}

int solution(vector<int> cookie) {
    int answer = 0;
    limit = cookie.size();
    // i까지 아들1의 과자
    for(int i=0; i<cookie.size() - 1; i++) {
        int left = i, right = i + 1;
        int left_sum = cookie[left], right_sum = cookie[right];
        while(!check_outside(left, right)) {
            if (left_sum == right_sum) answer = max(answer, left_sum);
            if (left > 0 && left_sum < right_sum) {
                left_sum += cookie[--left];
                continue;
            }
            else if (right < limit - 1 && right_sum < left_sum) {
                right_sum += cookie[++right];
                continue;
            } else break;
        }
    }
    return answer;
}