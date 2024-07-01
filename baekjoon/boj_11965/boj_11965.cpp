#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <numeric>

#define INF 987654321

using namespace std;

struct Person{
    int y, x, orange, dir, dist;

    bool operator<(Person other) const {
        return dist > other.dist;
    }
};
int sizeY = 0, sizeX = 0, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<vector<int> > maps;
vector<vector<vector<vector<int> > > > visited;

Person make_person(int y, int x, int orange, int dir, int dist) {
    Person person;
    person.y = y;
    person.x = x;
    person.dir = dir;
    person.orange = orange;
    person.dist = dist;
    return person;
}

bool check_outside(int y, int x) {
    return y < 0 || y >= sizeY || x < 0 || x >= sizeX;
}
int bfs() {
    priority_queue<Person> pq;
    pq.push(make_person(0, 0, 0, 0, 0));
    visited[0][0][0][0] = 0;
    while(!pq.empty()) {
        auto [y, x, orange, dir, dist] = pq.top(); pq.pop();
        if (visited[y][x][orange][dir] != dist) continue;
        for(int d=0; d<4; d++) {
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            int ndist = dist + 1;
            int norange = orange;
            if (check_outside(ny, nx) || maps[ny][nx] == 0 || (maps[ny][nx] == 3 && !norange) || visited[ny][nx][norange][d] < ndist) continue;

            while(maps[ny][nx] == 4) {
                norange = 0;
                if (check_outside(ny + moveY[d], nx + moveX[d]) || maps[ny + moveY[d]][nx + moveX[d]] == 0 || maps[ny + moveY[d]][nx + moveX[d]] == 3
                    || visited[ny + moveY[d]][nx + moveX[d]][norange][d] <= ndist)
                    break;
                visited[ny][nx][norange][d] = ndist;
                ny += moveY[d];
                nx += moveX[d];
                ndist++;
            }

            if (maps[ny][nx] == 1 || maps[ny][nx] == 2 || (maps[ny][nx] == 3 && norange) || maps[ny][ny] == 4) {
                if (maps[ny][nx] == 2) norange = 1;
                else if (maps[ny][nx] == 4) norange = 0;
                if (visited[ny][nx][norange][d] > ndist) {
                    pq.push(make_person(ny, nx, norange, d, ndist));
                    visited[ny][nx][norange][d] = ndist;
                }
            }
        }
    }
    int answer = min(
        INF, min(
            *min_element(visited[sizeY-1][sizeX-1][0].begin(), visited[sizeY-1][sizeX-1][0].end()),
            *min_element(visited[sizeY-1][sizeX-1][1].begin(), visited[sizeY-1][sizeX-1][1].end())
        )
    );
    return (answer == INF) ? -1 : answer;
}
int main(){
    cin>>sizeY>>sizeX;
    maps.resize(sizeY, vector<int>(sizeX, 0));
    visited.resize(sizeY, vector<vector<vector<int> > >(sizeX, vector<vector<int> >(2, vector<int>(4, INF))));
    for(int y=0; y<sizeY; y++) {
        for(int x=0; x<sizeX; x++) {
            cin>>maps[y][x];
        }
    }
    cout<<bfs();
}