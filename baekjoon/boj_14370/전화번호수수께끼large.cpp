#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

void solve(int test_case) {
    string origin;
    cin >> origin;

    vector<int> alpha_cnt(26, 0);
    for (char ch : origin) {
        alpha_cnt[ch - 'A']++;
    }

    vector<int> answer(10, 0);

    // 유니크한 알파벳이 포함된 숫자 우선 제거
    answer[0] = alpha_cnt['Z' - 'A'];  // ZERO
    answer[2] = alpha_cnt['W' - 'A'];  // TWO
    answer[4] = alpha_cnt['U' - 'A'];  // FOUR
    answer[6] = alpha_cnt['X' - 'A'];  // SIX
    answer[8] = alpha_cnt['G' - 'A'];  // EIGHT

    // 중복된 알파벳 제거
    answer[3] = alpha_cnt['H' - 'A'] - answer[8];  // THREE (H는 EIGHT에도 포함)
    answer[5] = alpha_cnt['F' - 'A'] - answer[4];  // FIVE (F는 FOUR에도 포함)
    answer[7] = alpha_cnt['S' - 'A'] - answer[6];  // SEVEN (S는 SIX에도 포함)
    answer[1] = alpha_cnt['O' - 'A'] - answer[0] - answer[2] - answer[4];  // ONE (O는 ZERO, TWO, FOUR에도 포함)
    answer[9] = alpha_cnt['I' - 'A'] - answer[5] - answer[6] - answer[8];  // NINE (I는 FIVE, SIX, EIGHT에도 포함)

    // 출력
    cout << "Case #" << test_case << ": ";
    for (int j = 0; j < 10; j++) {
        for (int k = 0; k < answer[j]; k++) {
            cout << j;
        }
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int test_case;
    cin >> test_case;

    for (int i = 1; i <= test_case; i++) {
        solve(i);
    }
}
