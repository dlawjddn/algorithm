#include <set>
#include <string>
#include <vector>
#include <iostream>

using namespace std;
struct Info{
    int y, x;
    char dir;
    
    bool operator<(const Info& other) const {
        if (y != other.y) return y < other.y;
        if (x != other.x) return x < other.x;
        return dir < other.dir;
    }
};
set<Info> visited;

void print_visited(){
    for(auto visit : visited){
        cout<<visit.y<<" "<<visit.x<<" "<<visit.dir<<"\n";
    }
}

bool check_outside(int y, int x){
    return y < -5 || y > 5 || x < -5 || x > 5;
}

Info make_info(int y, int x, char dir){
    Info info;
    info.y = y;
    info.x = x;
    info.dir = dir;
    return info;
}

int move_person(string dirs){
    int y = 0, x = 0;
    for(auto dir : dirs){
        int ny = y , nx = x;
        char rdir;
        if (dir == 'U'){
            ny += 1;
            rdir = 'D';
        }
        else if (dir == 'D'){
            ny -= 1;
            rdir = 'U';
        }
        else if (dir == 'R'){
            nx += 1;
            rdir = 'L';
        }
        else {
            nx -= 1;
            rdir = 'R';
        }
        if (check_outside(ny, nx)) continue;
        visited.insert(make_info(y, x, dir));
        y = ny;
        x = nx;
        visited.insert(make_info(ny, nx, rdir));
    }
    //print_visited();
    return visited.size() / 2;
}
int solution(string dirs) {
    return move_person(dirs);
}