#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <numeric>

using namespace std;

struct Person{
    int y, x, dir, cost;
    bool orange;

    bool operator<(Person other) const {
        return cost > other.cost;
    }
};
int sizeY = 0, sizeX = 0, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<vector<int> > maps;
vector<vector<vector<int> > > visited;

void print_visited(){
    for(int d=0; d<4; d++) {
        cout<<"d: "<<d<<"\n";
        for(int y=0; y<sizeY; y++) {
            for(int x=0; x<sizeX; x++) {
                if (visited[y][x][d] == 987654321) cout<<"-1 ";
                else cout<<visited[y][x][d]<<" ";
            }
            cout<<"\n";
        }
        cout<<"\n";
    }
}

Person make_person(int y, int x, int dir, int cost, bool orange) {
    Person person;
    person.y = y;
    person.x = x;
    person.dir = dir;
    person.cost = cost;
    person.orange = orange;
    return person;
}

bool check_outside(int y, int x) {
    return y < 0 || y >= sizeY || x < 0 || x>= sizeX;
}

void bfs(){
    priority_queue<Person> pq;
    pq.push(make_person(0, 0, 0, 0, false));
    pq.push(make_person(0, 0, 1, 0, false));
    visited[0][0][0] = 0;
    visited[0][0][1] = 0;
    while(!pq.empty()) {
        Person now = pq.top(); pq.pop();
        //cout<<now.y<<" "<<now.x<<"\n";
        if (visited[now.y][now.x][now.dir] != now.cost) continue;
        for(int d=0; d<4; d++) {
            int ny = now.y + moveY[d];
            int nx = now.x + moveX[d];
            int ncost = now.cost + 1;
            if (check_outside(ny, nx) || (visited[ny][nx][d] <= ncost) || maps[ny][nx] == 0 || (maps[ny][nx] == 3 && !now.orange)) continue;
            
            while (maps[ny][nx] == 4) {
                //cout<<"next!! "<<ny<<" "<<nx<<"\n";
                if (check_outside(ny + moveY[d], nx + moveX[d]) || maps[ny + moveY[d]][nx + moveX[d]] == 0 || (maps[ny + moveY[d]][nx + moveX[d]] == 3 && !now.orange))
                    break;
                visited[ny][nx][d] = ncost;
                ny += moveY[d];
                nx += moveX[d];
                ncost++;
            }

            if (maps[ny][nx] == 1 || maps[ny][nx] == 2 || (maps[ny][nx] == 3 && now.orange) || maps[ny][nx] == 4) {
                if (maps[ny][nx] == 2) now.orange = true;
                if (maps[ny][nx] == 4) now.orange = false;
                if (visited[ny][nx][d] > ncost) {
                    visited[ny][nx][d] = ncost;
                    pq.push(make_person(ny, nx, d, ncost, now.orange));
                }
            }
        }
    }
}

int main(){
    cin>>sizeY>>sizeX;
    maps.resize(sizeY, vector<int>(sizeX, 0));
    visited.resize(sizeY, vector<vector<int> >(sizeX, vector<int>(4, 987654321)));
    for(int y=0; y<sizeY; y++) {
        for(int x=0; x<sizeX; x++) {
            cin>>maps[y][x];
        }
    }
    bfs();
    int answer = *min_element(visited[sizeY-1][sizeX-1].begin(), visited[sizeY-1][sizeX-1].end());
    if (answer == 987654321) cout<<"-1";
    else cout<<answer;
    //print_visited();
}