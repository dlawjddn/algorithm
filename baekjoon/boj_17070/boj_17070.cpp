#include <iostream>
using namespace std;
int map[17][17], move_x[3]={1,0,1}, move_y[4]={0,1,1}, area=0, ans=0;
void dfs(int y, int x, int dir)
{
    if (y==area && x==area)
    {
        ans++;
        return;
    }
    for(int d=0; d<3; d++)
    {
        int ny=y+move_y[d], nx=x+move_x[d];
        if (dir==0 && d==1 || dir==1 && d==0) continue;
        if (ny>0 && ny<=area && nx>0 && nx<=area && map[ny][nx]==0)
        {
            if (d==2 && (map[y+1][x]==1 || map[y][x+1]==1)) continue;
            dfs(ny, nx, d);
        }
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin>>area;
    for(int i=1; i<=area; i++)
    {
        for(int j=1; j<=area; j++)
        {
            cin>>map[i][j];
        }
    }
    dfs(1,2,0);
    cout<<ans;
}