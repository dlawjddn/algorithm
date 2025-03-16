#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, S;
    cin >> N;
    
    vector<int> nums(N);
    for (int i = 0; i < N; i++) {
        cin >> nums[i];
    }
    
    cin >> S;

    for (int i = 0; i < N - 1 && S > 0; i++) {
        // 현재 위치 i에서 S 범위 내에서 최대값 찾기
        int maxIdx = i;
        for (int j = i + 1; j < N && j <= i + S; j++) {
            if (nums[j] > nums[maxIdx]) {
                maxIdx = j;
            }
        }

        // maxIdx가 i가 아니면 S 감소 및 한 칸씩 앞으로 당기기
        for (int j = maxIdx; j > i; j--) {
            swap(nums[j], nums[j - 1]);
        }

        // S에서 사용한 swap 횟수 차감
        S -= (maxIdx - i);
    }

    // 결과 출력
    for (int i = 0; i < N; i++) {
        cout << nums[i] << " ";
    }

    return 0;
}
