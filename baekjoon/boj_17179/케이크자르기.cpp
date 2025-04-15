#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> points;

int main() {
    int test_case, point_cnt, total_len;
    cin >> test_case >> point_cnt >> total_len;

    for (int i = 0; i < point_cnt; i++) {
        int point;
        cin >> point;
        points.push_back(point);
    }
    sort(points.begin(), points.end());
    points.push_back(total_len); // 마지막 조각 고려

    for (int t = 0; t < test_case; t++) {
        int div;
        cin >> div;

        int left = 1, right = total_len;
        int answer = 0;

        while (left <= right) {
            int mid = (left + right) / 2;
            int cnt = 0, before = 0;

            for (int i = 0; i < points.size(); i++) {
                if (points[i] - before >= mid) {
                    cnt++;
                    before = points[i];
                }
            }

            if (cnt >= div + 1) {
                answer = mid;         // 조건 만족 → 정답 후보
                left = mid + 1;       // 더 긴 길이 도전
            } else {
                right = mid - 1;
            }
        }

        cout << answer << "\n";
    }

    return 0;
}
