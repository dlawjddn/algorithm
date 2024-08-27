#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

int sizeY=0, sizeX=0, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<vector<char> > map(50, vector<char>(50, '.'));
vector<vector<int> > visited(50, vector<int>(50, 987654321));
vector<vector<int> > water(50, vector<int>(50, 0));
queue<pair<int, int> > rain;
queue<pair<int, int> > person;

void print_map(){
    for(int y=0; y<sizeY; y++){
        for(int x=0; x<sizeX; x++){
            cout<<map[y][x]<<" ";
        }
        cout<<"\n";
    }
}

void print_visited(){
    for(int y=0; y<sizeY; y++){
        for(int x=0; x<sizeX; x++){
            cout<<visited[y][x]<<" ";
        }
        cout<<"\n";
    }
}

bool check_outside(int y, int x){
    return y < 0 || y >= sizeY || x<0 || x >= sizeX;
}

void flood_water(){
    while(!rain.empty()){
        int y = rain.front().first;
        int x = rain.front().second; rain.pop();
        for(int d=0; d<4; d++){
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            if (check_outside(ny, nx) || visited[ny][nx] <= visited[y][x] + 1 || map[ny][nx] != '.') continue;
            rain.push(make_pair(ny, nx));
            visited[ny][nx] = visited[y][x] + 1;
        }
    }
}

int move_person(){
    while(!person.empty()){
        int y = person.front().first;
        int x = person.front().second; person.pop();
        for(int d=0; d<4; d++){
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            if (check_outside(ny, nx) || visited[ny][nx] <= visited[y][x] + 1 || map[ny][nx] == 'X') continue;
            if (map[ny][nx] == 'H'){
                return visited[y][x];
            }
            person.push(make_pair(ny, nx));
            visited[ny][nx] = visited[y][x] + 1; 
        }
    }
    return -1;
}
int main(int argc, char** argv)
{
    cin>>sizeY>>sizeX;
    for(int y=0; y<sizeY; y++){
        string s;
        cin>>s;
        for(int x=0; x<sizeX; x++){
            map[y][x] = s[x];
            if (map[y][x] == '*'){
                rain.push(make_pair(y, x));
                visited[y][x] = 1;
            }
            else if (map[y][x] == 'W'){
                person.push(make_pair(y, x));
                visited[y][x] = 1;
            }
        }
    }
    //print_map();
    flood_water();
    int answer = move_person();
    if (answer == -1)
        cout<<"FAIL";
    else
        cout<<answer;
}