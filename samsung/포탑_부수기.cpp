#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

int map[11][11], visited[11][11], moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
int last_attack[11][11];
int sizeY=0, sizeX=0, trial=0;
vector<int> shortest_dir;
struct Info{
    int y, x;
    vector<int> route;
};
void print_map(){
    cout<<"map\n";
    for(int y=1; y<=sizeY; y++){
        for(int x=1; x<=sizeX; x++){
            cout<<map[y][x]<<" ";
        }
        cout<<"\n";
    }
}
void print_visited(){
    cout<<"visited\n";
    for(int y=1; y<=sizeY; y++){
        for(int x=1; x<=sizeX; x++){
            cout<<visited[y][x]<<" ";
        }
        cout<<"\n";
    }
}
pair<int,int> find_last_attack(){
    int max_value = 0;
    pair<int, int> pos = make_pair(-1, -1);
    for(int y=1; y<=sizeY; y++){
        for(int x=1; x<=sizeX; x++){
            if (last_attack[y][x] == 0) continue;
            if (max_value < last_attack[y][x]){
                max_value = last_attack[y][x];
                pos.first = y;
                pos.second = x;
            }
        }
    }
    return pos;
}
pair<int, int> find_old_attack(){
    int min_value = 0;
    pair<int, int> pos = make_pair(-1, -1);
    for(int y=1; y<=sizeY; y++){
        for(int x=1; x<=sizeX; x++){
            if (last_attack[y][x] == 0) continue;
            if (min_value > last_attack[y][x]){
                min_value = last_attack[y][x];
                pos.first = y;
                pos.second = x;
            }
        }
    }
    return pos;
}
pair<int,int> choose_attacker(int t){
    pair<int, int> last_attacker = find_last_attack();
    int minY =0, minX=0, minA = 99999;
    if (!(last_attacker.first == -1 && last_attacker.second == -1)) {
        minA = map[last_attacker.first][last_attacker.second];
        minY = last_attacker.first;
        minX = last_attacker.second;
    }
    for(int y=sizeY; y>0; y--){
        for(int x=sizeX; x>0; x--){
            if (map[y][x] == 0) continue;
            if (minA > map[y][x]){
                minA = map[y][x];
                minY = y;
                minX = x;
            }
        }
    }
    map[minY][minX] += (sizeY + sizeX);
    last_attack[minY][minX] = t + 1;
    // cout<<map[minY][minX]<<" "<<minY<<" "<<minX<<"\n";
    return make_pair(minY, minX);
}
pair<int,int> choose_defenser(int ay, int ax){
    pair<int, int> old_attacker = find_old_attack();
    int maxY=0, maxX=0, maxA=0;
    if (!(old_attacker.first == -1 && old_attacker.second == -1)) {
        maxA = map[old_attacker.first][old_attacker.second];
        maxY = old_attacker.first;
        maxX = old_attacker.second;
    }
    for(int y=1; y<=sizeY; y++){
        for(int x=1; x<=sizeX; x++){
            if (ay == y && ax == x) continue;
            if (map[y][x] == 0) continue;
            if (map[y][x] > maxA){
                maxA = map[y][x];
                maxY = y;
                maxX = x;
            }
        }
    }
    // cout<<maxA<<" "<<maxY<<" "<<maxX<<"\n";
    return make_pair(maxY, maxX);
}
bool check_bound(int y, int x){
    return y>0 && y<=sizeY && x>0 && x<=sizeX;
}

bool try_attack(int sy, int sx, int ey, int ex){
    memset(visited, 0, sizeof(visited));
    queue<Info> q;
    Info start;
    start.y = sy;
    start.x = sx;;
    q.push(start);
    visited[sy][sx] = 1;
    while(!q.empty()){
        Info now = q.front(); q.pop();
        for(int d=0; d<4; d++){
            Info next = now;
            next.y = now.y + moveY[d];
            next.x = now.x + moveX[d];
            if (check_bound(next.y, next.x) && map[next.y][next.x] > 0 && visited[next.y][next.x] == 0){
                next.route.push_back(d);
                q.push(next);
                visited[next.y][next.x] = visited[next.y][next.x] + 1;
                if (next.y == ey && next.x == ex) {
                    shortest_dir = next.route;
                    return true;
                }
            }
        }
    }
    return false;
}

void lazer_attack(int sy, int sx){
    memset(visited, 0, sizeof(visited));
    int y = sy;
    int x = sx;
    int damage = map[sy][sx];
    visited[y][x] = 1;
    for(int i=0; i<shortest_dir.size(); i++){
        int ny = y + moveY[shortest_dir[i]];
        int nx = x + moveX[shortest_dir[i]];
        if (i == shortest_dir.size() - 1){
            map[ny][nx] -= damage;
            visited[ny][nx] = 1;
            if (map[ny][nx] < 0) map[ny][nx] = 0;
        } else {
            map[ny][nx] -= (damage / 2);
            visited[ny][nx] = 1;
            if (map[ny][nx] < 0) map[ny][nx] = 0;
        }
        y = ny;
        x = nx;
    }
    visited[sy][sx] = 1;
}
void bomb_attack(int sy, int sx, int ey, int ex){
    memset(visited, 0, sizeof(visited));
    int dy[8] = {-1,-1,-1,0,1,1,1,0};
    int dx[8] = {-1,0,1,1,1,0,-1,-1};
    map[ey][ex] -= map[sy][sx];
    if (map[ey][ex] < 0) map[ey][ex] = 0;
    visited[ey][ex] = 1;
    // cout<<"next position: \n";
    for(int d=0; d<8; d++){
        int ny = ey + dy[d];
        int nx = ex + dx[d];
        if (!check_bound(ny, nx)){
            if (ny > sizeY) ny = 1;
            else if (ny < 1) ny = sizeY;
            if (nx > sizeX) nx = 1;
            else if (nx < 1) nx = sizeX;
        }
        // cout<<d<<": "<<ny<<" "<<nx<<"\n";
        if (ny == sy && nx == sx) continue;
        if (map[ny][nx] == 0) continue;
        else {
            map[ny][nx] -= (map[sy][sx] / 2);
            visited[ny][nx] = 1;
            if (map[ny][nx] < 0) map[ny][nx] = 0;
        }
    }
    visited[sy][sx] = 1;
}
void repair(){
    for(int y=1; y<=sizeY; y++){
        for(int x=1; x<=sizeX; x++){
            if (visited[y][x] || map[y][x] == 0) continue;
            map[y][x]++;
        }
    }
}
void find_ans(){
    int ans = 0;
    for(int y=1; y<=sizeY; y++){
        for(int x=1; x<=sizeX; x++){
            if (ans < map[y][x]) ans = map[y][x];
        }
    }
    cout<<ans;
}
int main() {
    cin>>sizeY>>sizeX>>trial;
    for(int y=1; y<=sizeY; y++){
        for(int x=1; x<=sizeX; x++){
            cin>>map[y][x];
        }
    }
    for(int i=0; i<trial; i++){
        pair<int, int> attacker = choose_attacker(0);
        pair<int, int> defenser = choose_defenser(attacker.first, attacker.second);
        bool lazer = try_attack(attacker.first, attacker.second, defenser.first, defenser.second);
        if (lazer) lazer_attack(attacker.first, attacker.second);
        else bomb_attack(attacker.first, attacker.second, defenser.first, defenser.second);
        repair();
    }
    find_ans(); 
    // print_map();
    // print_visited();
    return 0;
}