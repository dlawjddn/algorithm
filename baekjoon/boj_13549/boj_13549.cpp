#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int MAXP = 100000;
const int INF = 1e9;

priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
vector<int> dist(200001, INF);

bool check_outside(int pos) {
    return pos < 0 || pos > MAXP;
}

int main() {
    int start, goal; 
    cin >> start >> goal;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [cnt, pos] = pq.top(); pq.pop();
        if (dist[pos] != cnt) continue;
        if (pos == goal) {
            cout << dist[goal] << "\n";
            break;
        }

        for (int d = 0; d < 3; d++) {
            if (d == 0) {
                // -1 이동
                int npos = pos - 1;
                int ncnt = cnt + 1;
                if (check_outside(npos) || dist[npos] <= ncnt) continue;
                dist[npos] = ncnt;
                pq.push({ncnt, npos});
            } else if (d == 1) {
                // +1 이동
                int npos = pos + 1;
                int ncnt = cnt + 1;
                if (check_outside(npos) || dist[npos] <= ncnt) continue;
                dist[npos] = ncnt;
                pq.push({ncnt, npos});
            } else {
                // *2 텔레포트
                int npos = pos * 2;
                int ncnt = cnt;
                if (check_outside(npos) || dist[npos] <= ncnt) continue;
                dist[npos] = ncnt;
                pq.push({ncnt, npos});
            }
        }
    }
}
