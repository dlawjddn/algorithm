#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> visited(1000001, 0);

void trace_back(int target) {
    // 역순으로 값을 출력
    vector<int> path;
    path.push_back(target);

    while (target > 1) {
        if (target % 3 == 0 && visited[target] == visited[target / 3] + 1) {
            target /= 3;
        } else if (target % 2 == 0 && visited[target] == visited[target / 2] + 1) {
            target /= 2;
        } else {
            target -= 1;
        }
        path.push_back(target);
    }
    for (int num : path) {
        cout << num << " ";
    }
    cout << "\n";
}

int main() {
    int target;
    cin >> target;

    queue<int> q;
    q.push(1);
    visited[1] = 0;

    while (!q.empty()) {
        int num = q.front();
        q.pop();

        // 연산 정의
        int mul3 = num * 3;
        if (mul3 <= 1000000 && visited[mul3] == 0) {
            visited[mul3] = visited[num] + 1;
            q.push(mul3);
        }

        int mul2 = num * 2;
        if (mul2 <= 1000000 && visited[mul2] == 0) {
            visited[mul2] = visited[num] + 1;
            q.push(mul2);
        }

        int plus1 = num + 1;
        if (plus1 <= 1000000 && visited[plus1] == 0) {
            visited[plus1] = visited[num] + 1;
            q.push(plus1);
        }

        // 목표값에 도달한 경우
        if (visited[target] != 0) {
            break;
        }
    }

    cout << visited[target] << "\n";
    trace_back(target);

    return 0;
}
