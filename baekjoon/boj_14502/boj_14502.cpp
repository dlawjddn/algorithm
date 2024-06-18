#include <iostream>
#include <queue>
#include <cstring>
#include <cmath>
using namespace std;
struct Point
{
    int x, y;
};
Point virus[10], space[64];
int map[8][8], cnt[8][8], visited[8][8], arr[3], move_x[4]={1,0,-1,0}, move_y[4]={0,1,0,-1}, size_x=0, size_y=0, ans=0, cnt_v=0, cnt_e=0;
void copy_map()
{
    for(int a=0; a<size_y; a++)
        for(int b=0; b<size_x; b++)
            cnt[a][b]=map[a][b];
}
void spread_virus()
{
    memset(visited, 0, sizeof(visited));
    copy_map();
    queue<pair<int, int> > q;
    for(int a=0; a<cnt_v; a++)
        q.push(make_pair(virus[a].y, virus[a].x));
    for(int b=0; b<3; b++)
        cnt[space[arr[b]].y][space[arr[b]].x]=1;
    while(!q.empty())
    {
        int y=q.front().first;
        int x=q.front().second; q.pop();
        for(int d=0; d<4; d++)
        {
            int ny=y+move_y[d], nx=x+move_x[d];
            if (ny>=0 && ny<size_y && nx>=0 && nx<size_x && visited[ny][nx]==0 && cnt[ny][nx]==0)
            {
                visited[ny][nx]=1;
                cnt[ny][nx]=cnt[y][x];
                q.push(make_pair(ny, nx));
            }
        }
    }
    int temp_cnt=0;
    for(int q=0; q<size_y; q++)
    {
        for(int w=0; w<size_x; w++)
        {
            if (cnt[q][w]==0)
            temp_cnt++;
        }
    }
    ans=max(ans, temp_cnt);
}
void find_out(int idx, int num)
{
    if (idx==2)
    {
        spread_virus();
        return ;
    }
    else
    {
        idx++;
        for(int b=num+1; b<cnt_e; b++)
        {
            arr[idx]=b;
            find_out(idx, b);
        }
    }
}
void combination()
{
    for(int a=0; a<cnt_e; a++)
    {
        int idx=0;
        arr[idx]=a;
        find_out(idx, a);
    }
    cout<<ans;
}
int main()
{
    cin>>size_y>>size_x;
    for(int i=0; i<size_y; i++)
    {
        for(int j=0; j<size_x; j++)
        {
            cin>>map[i][j];
            if (map[i][j]==2)
            {
                virus[cnt_v].y=i, virus[cnt_v].x=j;
                cnt_v++;
            }
            else if (map[i][j]==0)
            {
                space[cnt_e].y=i, space[cnt_e].x=j;
                cnt_e++;
            }
        }
    }
    combination();
} 