#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int> > map(20, vector<int>(20, 0));
vector<vector<int> > visited(20, vector<int>(20, 0));
vector<pair<int, int> > start;
int moveX[4]={1,0,-1,0}, moveY[4]={0,1,0,-1}, sq_size=0, start_cnt=0, answer=0;

void print_visited(){
    for(int y=0; y<sq_size; y++){
        for(int x=0; x<sq_size; x++){
            cout<<visited[y][x];
        }
        cout<<"\n";
    }
    cout<<"\n";
}
bool check_outside(int y, int x){
    // true: 범위 바깥
    // false: 범위 안
    return (y < 0 || y >= sq_size || x < 0 || x >=sq_size);
}
void dfs(int step, int cnt, int y, int x, int sum){
    visited[y][x] = step;
    sum += map[y][x];
    if (cnt == 4) {
        // 다음 단계를 위해 새로운 시작점으로 다시 dfs를 해야하는 경우
        if (step < start_cnt){
            dfs(step+1, 1, start[step].first, start[step].second, sum);
            //cout<<"hello\n";
        } else{
            //print_visited();
            answer = max(answer, sum);
        }
    }
    else{
        for(int d=0; d<4; d++){
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            if (check_outside(ny, nx) || visited[ny][nx] != 0) continue;
            dfs(step, cnt + 1, ny, nx, sum);
        }
    }
    if (cnt > 1)
        visited[y][x] = 0;
    sum -= map[y][x];
    //print_visited();
}
int main(int argc, char** argv)
{
    cin>>sq_size>>start_cnt;
    for(int y=0; y<sq_size; y++){
        for(int x=0; x<sq_size; x++){
            cin>>map[y][x];
        }
    }
    for(int i=0; i<start_cnt; i++){
        int startY=0, startX=0;
        cin>>startY>>startX;
        visited[--startY][--startX] = i+1;
        start.push_back(make_pair(startY, startX));
    }
    dfs(1, 1, start[0].first, start[0].second, 0);
    cout<<answer;
}