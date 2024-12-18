#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int player_cnt, answer = 0;
vector<int> scores(100001, 0);

int main() {
    cin>>player_cnt;
    for(int i=0; i<player_cnt; i++) {
        int score; cin>>score;
        scores[score]++;
    }
    int remain = 0;
    for(int i=1; i<=100000; i++) {
        if (scores[i] == 0) continue;
        int now_sum = scores[i] + remain;
        int add_group = now_sum / i;

        answer += add_group;
        remain = now_sum % i;
    }
    cout<<answer;
}


/**
 * @brief 정답 코드
 * 
 */

int main() {
    int n; cin>>n;
    vector<int> arr;

    for(int i=0; i<n; i++) {
        int x; cin>>x;
        arr.push_back(x);
    }

    sort(arr.begin(), arr.end());

    int result = 0, cnt = 0;
    for(int i=0; i<n; i++) {
        cnt += 1;
        if (cnt >= arr[i]) {
            result += 1;
            cnt = 0;
        }
    }

    cout<<result;
}