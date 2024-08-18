/**
 * @file 스티커모으기2_12971.cpp
 * @brief 프로그래머스 스티커 모으기 lv3
 * @version 0.1
 * @date 2024-05-27
 * 
 * @copyright Copyright (c) 2024
 * 
 * 전형적인 dp 문제
 * 뭘 선택하냐에 따라 결과가 달라지며, 현재 값이 최선이 아니더라도 마지막에는 최선의 선택이 되는 경우 파악
 * dp 인지 파악을 빠르게 하는 것이 관건인 문제...
 * 생각만 하면 빨리 할 수 있던 문제 인 듯..
 * 
 * 두번째 풀이지만.. 똑같이 또 틀렸다..
 * 
 * 이 문제가 디피인 이유, 결론적으로 양 옆의 스티커를 선택하지 못한다는 조건 때문에
 * 현재의 스티커는 자신의 위치보다 2만큼 앞에 있는 스티커를 고르고 자신을 고르는 경우, 자신보다 1만큼 앞선 스티커를 고르는 경우
 * 이렇게 두가지로 나뉘게 된다.. 따라서 dp[i-2] + sticker[i], dp[i-1] 중 큰 값을 선택해서 마지막에 오는 값이 정답이 된다..
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> sticker) {
    int n = sticker.size();
    if (n == 0) return 0;
    if (n == 1) return sticker[0];
    if (n == 2) return max(sticker[0], sticker[1]);

    vector<int> dp1(n, 0);
    vector<int> dp2(n, 0);

    // 첫번째 스티커를 선택하는 경우
    dp1[0] = sticker[0];
    dp1[1] = max(sticker[0], sticker[1]);
    for (int i = 2; i < n-1; i++) {
        dp1[i] = max(dp1[i-2] + sticker[i], dp1[i-1]);
    }

    // 두번째 스티커를 선택하는 경우
    dp2[0] = 0;
    dp2[1] = sticker[1];
    for (int i = 2; i < n; i++) {
        dp2[i] = max(dp2[i-2] + sticker[i], dp2[i-1]);
    }

    return max(dp1[n-2], dp2[n-1]);
}
