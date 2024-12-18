#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int ball_cnt, limit, answer = 0;
vector<int> balls;
vector<bool> visited;

void init() {
    balls.resize(ball_cnt);
    visited.resize(ball_cnt, false);
}

void combination(int idx, int depth) {
    visited[idx] = true;
    if (depth == 1) {
        answer ++;
        visited[idx] = false;
        return ;
    }
    for(int i=idx; i<ball_cnt; i++) {
        if (visited[i] || balls[idx] == balls[i]) continue;
        combination(i, depth + 1);
    }
    visited[idx] = false;
}

int main() {
    cin>>ball_cnt>>limit;
    init();
    for(int i=0; i<ball_cnt; i++) {
        cin>>balls[i];
    }
    for(int i=0; i<ball_cnt; i++) combination(i, 0);
    cout<<answer;

}

/**
 * @brief 정답 코드
 * 
 */

#include <iostream>
#include <vector>

using namespace std;

int main() {
    int ball_cnt, limit;
    cin >> ball_cnt >> limit;

    vector<int> weight_count(limit + 1, 0);
    vector<int> balls(ball_cnt);

    // 각 볼링공의 무게 개수 저장
    for (int i = 0; i < ball_cnt; i++) {
        cin >> balls[i];
        weight_count[balls[i]]++;
    }

    int result = 0;

    // 서로 다른 무게의 볼링공 조합 계산
    for (int i = 1; i <= limit; i++) {
        for (int j = i + 1; j <= limit; j++) {
            result += weight_count[i] * weight_count[j];
        }
    }

    cout << result << endl;

    return 0;
}
