#include <iostream>
#include <string>

using namespace std;

int len;
string answer = "";

bool check(string num) {
    int l = num.length();
    for (int i = 1; i <= l / 2; i++) {
        if (num.substr(l - i, i) == num.substr(l - 2 * i, i)) return false;
    }
    return true;
}

void dfs(string num) {
    if (!answer.empty()) return; // 이미 정답을 찾으면 종료
    if (num.length() == len) {
        answer = num;
        cout << answer << endl;
        exit(0); // 가장 작은 해를 찾으면 즉시 종료
    }

    for (char c : {'1', '2', '3'}) {
        if (check(num + c)) {
            dfs(num + c);
        }
    }
}

int main() {
    cin >> len;
    dfs("");
}
