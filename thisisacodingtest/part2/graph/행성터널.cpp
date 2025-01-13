#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Planet {
    int x, y, z;
};
struct Info {
    int node1, node2, cost;
    bool operator<(Info other) const {
        return cost > other.cost;
    }
};
int planet_cnt, answer = 0;
vector<int> parents;
vector<Planet> planets;
priority_queue<Info> pq;

int find_parent(int node) {
    if (node == parents[node]) return node;
    return parents[node] = find_parent(parents[node]);
}

void make_union(int node1, int node2) {
    int n1p = find_parent(node1);
    int n2p = find_parent(node2);
    if (n1p > n2p) swap(n1p, n2p);
    parents[n2p] = n1p;
}

bool is_valid(int node1, int node2) {
    return find_parent(node1) != find_parent(node2);
}

int cal_cost(int p1, int p2) {
    return min(
        {abs(planets[p1].x - planets[p2].x),
         abs(planets[p1].y - planets[p2].y),
         abs(planets[p1].z - planets[p2].z)
        }
    );
}

int main() {
    cin>>planet_cnt;
    for(int i=0; i<planet_cnt; i++) {
        int x, y, z; cin>>x>>y>>z;
        planets.push_back({x, y, z});
    }
    parents.resize(planet_cnt);
    for(int i=0; i<planet_cnt; i++) parents[i] = i;

    for (int axis = 0; axis < 3; axis++) {
        vector<pair<int, int>> coords; // {좌표값, 인덱스}
        for (int i = 0; i < planet_cnt; i++) {
            if (axis == 0) coords.push_back({planets[i].x, i});
            else if (axis == 1) coords.push_back({planets[i].y, i});
            else coords.push_back({planets[i].z, i});
        }

        // 좌표 기준 정렬
        sort(coords.begin(), coords.end());

        // 인접한 행성 간의 간선만 추가
        for (int i = 0; i < planet_cnt - 1; i++) {
            int cost = abs(coords[i].first - coords[i + 1].first);
            int node1 = coords[i].second;
            int node2 = coords[i + 1].second;
            pq.push({node1, node2, cost});
        }
    }
    
    int cnt = 0;
    while(!pq.empty() && cnt < planet_cnt - 1) {
        auto[node1, node2, cost] = pq.top(); pq.pop();
        if (is_valid(node1, node2)) {
            make_union(node1, node2);
            answer += cost;
            cnt++;
        }
    }
    cout<<answer;
}