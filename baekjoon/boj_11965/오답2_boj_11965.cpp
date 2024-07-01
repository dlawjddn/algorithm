#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <numeric>

#define INF 987654321

using namespace std;

struct Person{
    int y, x, dir, dist, orange;

    bool operator<(Person other) const {
        return dist > other.dist;
    }
};
int sizeY = 0, sizeX = 0, moveY[4] = {0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<vector<int> > maps;
vector<vector<vector<vector<int> > > > visited;

Person make_person(int y, int x, int dir, int dist, int orange) {
    Person person;
    person.y = y;
    person.x = x;
    person.dir = dir;
    person.dist = dist;
    person.orange = orange;
    return person;
}

bool check_outside(int y, int x) {
    return y < 0 || y >= sizeY || x < 0 || x >= sizeX;
}

void bfs() {
    priority_queue<Person> pq;
    pq.push(make_person(0, 0, 0, 0, 0));
    pq.push(make_person(0, 0, 1, 0, 0));
    visited[0][0][0][0] = 0;
    visited[0][0][0][1] = 0;
    while(!pq.empty()) {
        auto [y, x, dir, dist, orange] = pq.top(); pq.pop();
        //if (visited[y][x][orange][dir] != dist) continue;
        for(int d=0; d<4; d++) {
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            int ndist = dist + 1;
            // 다음 칸이 진행이 안 되는 경우
            if (check_outside(ny, nx) || visited[ny][nx][orange][d] <= ndist || maps[ny][nx] == 0 || (maps[ny][nx] == 3 && !orange) )
                continue;
            
            // 다음 칸이 보라색인 경우 -> 미끄러지듯 진행, 이동해야하는 마지막 칸까지 움직이고 멈춤
            while(maps[ny][nx] == 4) {
                if (check_outside(ny + moveY[d], nx + moveX[d]) || visited[ny + moveY[d]][nx + moveX[d]][orange][d] <= ndist 
                    || maps[ny + moveY[d]][nx + moveX[d]] == 0 || (maps[ny + moveY[d]][nx + moveX[d]] == 3 && !orange))
                    break;
                visited[ny][nx][orange][d] = ndist;
                ny += moveY[d];
                nx += moveX[d];
                ndist++;
            }

            // 다음 칸이 보락색이 아닌 경우 or 보라색에서 이동한 뒤 마지막칸
            if (maps[ny][nx] == 1 || maps[ny][nx] == 2 || (maps[ny][nx] == 3 && orange) || maps[ny][nx] == 4) {
                if (maps[ny][nx] == 2) orange = 1;
                else if (maps[ny][nx] == 4) orange = 0;
                if (visited[ny][nx][orange][d] < ndist) continue;
                visited[ny][nx][orange][d] = ndist;
                pq.push(make_person(ny, nx, d, ndist, orange));
            }
        }
    }
}

int main(){
    int answer = INF;
    cin>>sizeY>>sizeX;
    maps.resize(sizeY, vector<int>(sizeX, 0));
    visited.resize(sizeY, vector<vector<vector<int> > >(sizeX, vector<vector<int> >(2, vector<int>(4, INF))));
    for(int y=0; y<sizeY; y++) {
        for(int x=0; x<sizeX; x++) {
            cin>>maps[y][x];
        }
    }
    bfs();
    answer = min(answer, 
        min(
            *min_element(visited[sizeY-1][sizeX-1][0].begin(), visited[sizeY-1][sizeX-1][0].end()),
            *min_element(visited[sizeY-1][sizeX-1][1].begin(), visited[sizeY-1][sizeX-1][1].end())
        )
    );
    if (answer == INF) cout<<"-1";
    else cout<<answer;

}