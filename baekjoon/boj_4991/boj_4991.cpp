#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
struct Point{
    int y, x;
};
Point dirty[11];
int map[21][21], visited[21][21][11], move_x[4]={1,0,-1,0}, move_y[4]={0,1,0,-1}, size_x=0, size_y=0, cnt=987654321, dirty_cnt=1, start_y=0, start_x=0;
void find_out(int num){
    queue<pair<int, int> > q;
    q.push(make_pair(dirty[num].y, dirty[num].x));
    visited[dirty[num].y][dirty[num].x][num]=1;
    while(!q.empty()){
        int y=q.front().first;
        int x=q.front().second; q.pop();
        for(int d=0; d<4; d++){
            int ny=y+move_y[d], nx=x+move_x[d];
            if (ny>=0 && ny<size_y && nx>=0 && nx<size_x && map[ny][nx]!=-1 && visited[ny][nx][num]==0){
                visited[ny][nx][num]=visited[y][x][num]+1;
                q.push(make_pair(ny, nx));
            }
        }
    }
}
int check_dist(vector <int> v){
    int temp_cnt=visited[dirty[v[0]].y][dirty[v[0]].x][0]-1;
    for(int a=0; a<v.size()-1; a++){
        temp_cnt+=abs(visited[dirty[v[a+1]].y][dirty[v[a+1]].x][v[a]]-1);
        if (visited[dirty[v[a]].y][dirty[v[a]].x][v[a]]==0 || visited[dirty[v[a-1]].y][dirty[v[a-1]].x][v[a+1]]==0)
        return 0;
    }
    cnt=min(cnt, temp_cnt);
    return 1;
}
int main(){
    while(1){
        cin>>size_x>>size_y;
        if (size_x==0 && size_y==0) break;
        memset(map, 0, sizeof(map));
        memset(visited, 0, sizeof(visited));
        memset(dirty, -1, sizeof(dirty));
        dirty_cnt=1;
        cnt=987654321;
        for(int i=0; i<size_y; i++){
            string s;
            cin>>s;
            for(int j=0; j<size_x; j++){
                if (s[j]=='.') map[i][j]=0;
                else if (s[j]=='x') map[i][j]=-1;
                else if (s[j]=='o'){
                    map[i][j]=0;
                    start_y=i, start_x=j;
                    dirty[0].y=i, dirty[0].x=j;
                }
                else if (s[j]=='*'){
                    map[i][j]=dirty_cnt;
                    dirty[dirty_cnt].y=i, dirty[dirty_cnt].x=j;
                    dirty_cnt++;
                }
            }
        }
        vector<int> v;
        bool flag=false;
        for(int a=1; a<dirty_cnt; a++) v.push_back(a);
        for(int a=0; a<dirty_cnt; a++) find_out(a);
        do{
            if (!check_dist(v)){
                flag=true;
                break;
            }
        }
        while(next_permutation(v.begin(), v.end()));
        if (flag) cout<<"-1\n";
        else cout<<cnt<<"\n";
    }
}