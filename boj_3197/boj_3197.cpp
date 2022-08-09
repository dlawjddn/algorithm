#include <iostream>
#include <queue>
using namespace std;
char map[1501][1501];
bool FIND=false, visited[1500][1500];
int move_x[4]={1,0,-1,0}, move_y[4]={0,1,0,-1}, size_y=0, size_x=0, start_y=0, start_x=0;
queue<pair<int, int> > swan, swan_n, water, water_n;
void melting_ice()
{
    while(!water.empty())
    {
        int y=water.front().first;
        int x=water.front().second; water.pop();
        for(int d=0; d<4; d++)
        {
            int ny=y+move_y[d], nx=x+move_x[d];
            if (ny>=0 && ny<size_y && nx>=0 && nx<size_x)
            {
                if (map[ny][nx]=='X')
                {
                    map[ny][nx]='.';
                    water_n.push(make_pair(ny, nx));
                }
            }
        }
    }
}
void moving_swan()
{
    while(!swan.empty())
    {
        int y=swan.front().first;
        int x=swan.front().second; swan.pop();
        for(int d=0; d<4; d++)
        {
            int ny=y+move_y[d], nx=x+move_x[d];
            if (ny>=0 && ny<size_y && nx>=0 && nx<size_x && visited[ny][nx]==false)
            {
                if (map[ny][nx]=='.')
                {
                    swan.push(make_pair(ny, nx));
                    visited[ny][nx]=true;
                }
                else if (map[ny][nx]=='L')
                {
                    FIND=true;
                    visited[ny][nx]=true;
                    return ;
                }
                else
                {
                    swan_n.push(make_pair(ny, nx));
                    visited[ny][nx]=true;
                }
            }
        }
    }
}
void count_days()
{
    int cnt=0;
    swan.push(make_pair(start_y, start_x));
    visited[start_y][start_x]=true;
    while(!FIND)
    {
        moving_swan();
        if (!FIND)
        {
            melting_ice();
            swan=swan_n;
            water=water_n;
            while(!swan_n.empty()) swan_n.pop();
            while(!water_n.empty()) water_n.pop();
            cnt++;
        }
    }
    cout<<cnt;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin>>size_y>>size_x;
    for(int i=0; i<size_y; i++)
    {
        cin>>map[i];
        for(int j=0; j<size_x; j++)
        {
            if (map[i][j]=='L')
            {
                start_y=i; start_x=j;
            }
            if (map[i][j]!='X')
            water.push(make_pair(i, j));
        }
    }
    count_days();
}