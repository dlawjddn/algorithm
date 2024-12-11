#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int main() {
    int answer = 0, number, div; cin>>number>>div;
    while(number >= div) {
        while(number % div != 0) {
            number--;
            answer++;
        }
        number /= div;
        answer++;
    }
    while(number > 1) {
        number--;
        answer++;
    }
    cout<<answer;
}

/**
 * @brief 조건에 따라 시간초과가 발생할 수 있는 코드
 * 
 */

// queue<pair<int, int> > q;
// vector<bool> visited;

// int main() {
//     int number, mod; cin>>number>>mod;
//     visited.resize(number + 1, false);
//     q.push({number, 0});
//     while(!q.empty()) {
//         auto[num, cnt] = q.front(); q.pop();
//         if (num == 1) {
//             cout<<cnt;
//             break;
//         }
//         if (!visited[num - 1]) {
//             q.push({num-1, cnt + 1});
//             visited[num-1] = true;
//         }
//         if (!visited[num / mod]) {
//             q.push({num / mod, cnt + 1});
//             visited[num / mod] = true;
//         }
//     }
// }