#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// D 연산: 현재 값의 2배 (10000 이상이면 10000으로 나눈 나머지)
int D(int num) {
    return (num * 2) % 10000;
}

// S 연산: 현재 값 -1 (0이면 9999)
int S(int num) {
    return (num == 0) ? 9999 : num - 1;
}

// L 연산: 왼쪽으로 회전 (예: 1234 -> 2341)
int L(int num) {
    return (num % 1000) * 10 + num / 1000;
}

// R 연산: 오른쪽으로 회전 (예: 1234 -> 4123)
int R(int num) {
    return (num % 10) * 1000 + num / 10;
}

void bfs(int src, int dest) {
    queue<pair<int, string>> q;
    vector<bool> visited(10000, false);

    q.push({src, ""});
    visited[src] = true;

    while (!q.empty()) {
        int num = q.front().first;
        string path = q.front().second;
        q.pop();

        if (num == dest) {
            cout << path << "\n";
            return;
        }

        // D 연산
        int d_num = D(num);
        if (!visited[d_num]) {
            visited[d_num] = true;
            q.push({d_num, path + "D"});
        }

        // S 연산
        int s_num = S(num);
        if (!visited[s_num]) {
            visited[s_num] = true;
            q.push({s_num, path + "S"});
        }

        // L 연산
        int l_num = L(num);
        if (!visited[l_num]) {
            visited[l_num] = true;
            q.push({l_num, path + "L"});
        }

        // R 연산
        int r_num = R(num);
        if (!visited[r_num]) {
            visited[r_num] = true;
            q.push({r_num, path + "R"});
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int test_case;
    cin >> test_case;

    for (int t = 0; t < test_case; t++) {
        int src, dest;
        cin >> src >> dest;
        bfs(src, dest);
    }
}
