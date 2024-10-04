#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <set>

using namespace std;

struct Info {
    int node1, node2, cost;
    bool operator<(Info other) const {
        return cost > other.cost;
    }
};
int sizeY = 0, sizeX = 0, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
int island_cnt = 0;
vector<Info> edges;
vector<int> parents;
vector<vector<int> > maps;
vector<vector<bool> > visited;
unordered_map<int, vector<pair<int, int> > > islands;
priority_queue<Info> pq;

void print_maps() {
    for(int y=0; y<sizeY; y++) {
        for(int x=0; x<sizeX; x++) {
            cout<<maps[y][x]<<" ";
        }
        cout<<"\n";
    }
}

void print_islands() {
    for(auto island : islands) {
        cout<<island.first<<"\n";
        for(int i=0; i<island.second.size(); i++) {
            cout<<"("<<island.second[i].first<<","<<island.second[i].second<<") ";
        }
        cout<<"\n";
    }
}

void print_edges() {
    for(auto edge : edges) {
        cout<<edge.node1<<" "<<edge.node2<<" "<<edge.cost<<"\n";
    }
    cout<<"\n";
}

int find_parent(int node) {
    if (node == parents[node]) return node;
    return parents[node] = find_parent(parents[node]);
}

void make_union(int parent, int child) {
    parent = find_parent(parent);
    child = find_parent(child);
    if (parent > child) swap(parent, child);
    parents[child] = parent;
}

bool is_same_parent(int node1, int node2) {
    return find_parent(node1) == find_parent(node2);
}

bool check_outside(int y, int x) {
    return y < 0 || y >= sizeY || x < 0 || x >= sizeX;
}

void make_edges() {
    for(int i=1; i<=island_cnt; i++) {
        for(int j=0; j<islands[i].size(); j++) {
            auto[y, x] = islands[i][j];
            for(int d=0; d<4; d++) {
                int ny = y + moveY[d];
                int nx = x + moveX[d];
                if (check_outside(ny, nx) || maps[ny][nx] != 0) continue;
                int cnt = 0;
                bool success = true;
                while(maps[ny][nx] == 0) {
                    cnt++;
                    ny += moveY[d];
                    nx += moveX[d];
                    if (check_outside(ny, nx)) {
                        success = false;
                        break;
                    }
                }
                if (success && cnt >= 2) edges.push_back({i, maps[ny][nx], cnt});
            }
        }
    }
}


void bfs(int sy, int sx) {
    ++island_cnt;
    queue<pair<int, int> > q;
    q.push({sy, sx});
    islands[island_cnt].push_back({sy, sx});
    maps[sy][sx] = island_cnt;
    visited[sy][sx] = true;
    while(!q.empty()) {
        auto[y, x] = q.front(); q.pop();
        for(int d=0; d<4; d++) {
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            if (check_outside(ny, nx) || visited[ny][nx] || maps[ny][nx] == 0) continue;
            q.push({ny, nx});
            islands[island_cnt].push_back({ny, nx});
            maps[ny][nx] = island_cnt;
            visited[ny][nx] = true;
        }
    }
}

void div_island() {
    for(int y=0; y<sizeY; y++) {
        for(int x=0; x<sizeX; x++) {
            if (visited[y][x] || maps[y][x] == 0) continue;
            bfs(y, x);
        }
    }
}

int make_mst() {
    int cnt = 0, total_cost = 0;
    parents.resize(island_cnt + 1);
    for(int i=1; i<parents.size(); i++) parents[i] = i;
    for(auto edge : edges) {
        pq.push({edge.node1, edge.node2, edge.cost});
    }
    while(!pq.empty()) {
        auto[node1, node2, cost] = pq.top(); pq.pop();
        if (is_same_parent(node1, node2)) continue;
        make_union(node1, node2);
        cnt += 1;
        total_cost += cost;
    }
    return (cnt == island_cnt - 1) ? total_cost : -1;
}

int main(){
    cin>>sizeY>>sizeX;
    maps.resize(sizeY, vector<int>(sizeX, 0));
    visited.resize(sizeY, vector<bool>(sizeX, false));
    for(int y=0; y<sizeY; y++) {
        for(int x=0; x<sizeX; x++) {
            cin>>maps[y][x];
        }
    }
    div_island();
    make_edges();
    //print_edges();
    cout<<make_mst();
}