#include <iostream>
#include <vector>

using namespace std;

int main() {
    int ccnt; cin >> ccnt;
    string str = "";
    for (int i = 0; i < ccnt; i++) {
        char c; cin >> c;
        str += c;
    }

    int left = 0, right = ccnt - 1;
    string answer = "";

    while (left <= right) {
        int l = left, r = right;
        while (l < r && str[l] == str[r]) {
            l++;
            r--;
        }

        if (l < r && str[l] < str[r]) {
            answer += str[left++];
        } else {
            answer += str[right--];
        }
    }

    for (int i = 0; i < answer.size(); i++) {
        if ((i + 1) % 80 == 0) cout << answer[i] << "\n";
        else cout << answer[i];
    }
}
