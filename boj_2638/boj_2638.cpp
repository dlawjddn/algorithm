#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
queue<pair<int, int> > out, cheese;
int map[100][100], visited[100][100], move_x[4]={1,0,-1,0}, move_y[4]={0,1,0,-1}, size_y=0, size_x=0, cnt=0;
void check_outside(int y, int x)
{
    visited[y][x]=1;
    for(int d=0; d<4; d++)
    {
        int ny=y+move_y[d], nx=x+move_x[d];
        if (ny>=0 && ny<size_y && nx>=0 && nx<size_x && visited[ny][nx]==0 && map[ny][nx]==0)
        check_outside(ny, nx);
    }
}
int melting_cheese()
{
    int over=0;
    for(int i=0; i<size_y; i++)
    {
        for(int j=0; j<size_x; j++)
        {
            if (map[i][j]==1)
            cheese.push(make_pair(i, j));
        }
    }
    while(!cheese.empty())
    {
        int y=cheese.front().first;
        int x=cheese.front().second; cheese.pop();
        int check=0;
        for(int d=0; d<4; d++)
        {
            int ny=y+move_y[d], nx=x+move_x[d];
            if (ny>=0 && ny<size_y && nx>=0 && nx<size_x)
            {
                if (visited[ny][nx]==1)
                check++;
            }
        }
        if (check>=2)
        {
            map[y][x]=0;
            over++;
        }
    }
    return over;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin>>size_y>>size_x;
    for(int i=0; i<size_y; i++)
    {
        for(int j=0; j<size_x; j++)
        {
            cin>>map[i][j];
        }
    }
    while(1)
    {
        check_outside(0, 0);
        if (!melting_cheese())
        break;
        cnt++;
        memset(visited, 0, sizeof(visited));
    }
    cout<<cnt;
}