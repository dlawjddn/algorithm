#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool isPossible(const vector<int>& lectures, int M, int capacity) {
    int count = 1;  // 블루레이 개수
    int sum = 0;

    for (int length : lectures) {
        if (sum + length > capacity) {
            count++;
            sum = 0;
        }
        sum += length;
    }

    return count <= M;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<int> lectures(N);
    int maxLength = 0;
    int totalSum = 0;

    for (int i = 0; i < N; ++i) {
        cin >> lectures[i];
        maxLength = max(maxLength, lectures[i]);
        totalSum += lectures[i];
    }

    int left = maxLength;
    int right = totalSum;
    int answer = totalSum;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (isPossible(lectures, M, mid)) {
            answer = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    cout << answer << '\n';
    return 0;
}
