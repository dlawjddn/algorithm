#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 최대 꿀의 양을 구하는 함수
long long getMaxHoney(const vector<int>& honey, int N) {
    vector<long long> prefixSum(N, 0);
    
    // 누적 합 계산
    prefixSum[0] = honey[0];
    for (int i = 1; i < N; i++) {
        prefixSum[i] = prefixSum[i - 1] + honey[i];
    }

    long long maxHoney = 0;

    // Case 1: 벌통이 오른쪽 끝, 벌 2마리 중 한 마리는 왼쪽 끝
    for (int i = 1; i < N - 1; i++) {
        long long honeyAmount = (prefixSum[N - 1] - honey[0] - honey[i]) + (prefixSum[N - 1] - prefixSum[i]);
        maxHoney = max(maxHoney, honeyAmount);
    }

    // Case 2: 벌통이 왼쪽 끝, 벌 2마리 중 한 마리는 오른쪽 끝
    for (int i = 1; i < N - 1; i++) {
        long long honeyAmount = (prefixSum[N - 2] - honey[i]) + (prefixSum[i - 1]);
        maxHoney = max(maxHoney, honeyAmount);
    }

    // Case 3: 벌통이 중간에 있고, 벌 2마리는 양쪽 끝
    for (int i = 1; i < N - 1; i++) {
        long long honeyAmount = (prefixSum[i] - honey[0]) + (prefixSum[N - 1] - prefixSum[i - 1] - honey[N - 1]);
        maxHoney = max(maxHoney, honeyAmount);
    }

    return maxHoney;
}

int main() {
    int N;
    cin >> N;
    vector<int> honey(N);
    
    for (int i = 0; i < N; i++) {
        cin >> honey[i];
    }

    cout << getMaxHoney(honey, N) << endl;

    return 0;
}
