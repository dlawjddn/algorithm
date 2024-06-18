#include <iostream>
#include <cstring>
using namespace std;
bool flag=false, stop=false;
int map[100][10], visited[100][10], will_be_break[100][10], move_x[4]={1,0,-1,0}, move_y[4]={0,1,0,-1}, size_y=0, size_x=10, rule=0, cnt=0;
void get_low()
{
    for(int x=0; x<size_x; x++)
    {
        int empty=0;
        for(int y=size_y-1; y>=0; y--)
        {
            if (map[y][x]==0)
            empty++;
            else if (map[y][x]!=0 && empty!=0)
            {
                map[y+empty][x]=map[y][x];
                map[y][x]=0;
            }
        }
    }
}
void delete_block()
{
    stop=true;
    for(int a=0; a<size_y; a++)
    {
        for(int b=0; b<size_x; b++)
        {
            if (will_be_break[a][b]==1)
            {
                map[a][b]=0;
                stop=false;
            }
        }
    }
    memset(will_be_break, 0, sizeof(will_be_break));
    get_low();
}
void use_dfs(int y, int x)
{
    visited[y][x]=1;
    cnt++;
    if (cnt>=rule)
    flag=true;
    for(int d=0; d<4; d++)
    {
        int ny=y+move_y[d], nx=x+move_x[d];
        if (ny>=0 && ny<size_y && nx>=0 && nx<size_x && visited[ny][nx]==0 && map[y][x]==map[ny][nx])
        use_dfs(ny, nx);
    }
}
void solve()
{
    for(int a=0; a<size_y; a++)
    {
        for(int b=0; b<size_x; b++)
        {
            cnt=0;
            if (visited[a][b]==0 && map[a][b]!=0)
            use_dfs(a, b);
            if (flag)
            {
                for(int a=0; a<size_y; a++)
                {
                    for(int b=0; b<size_x; b++)
                    {
                        if (visited[a][b]==1)
                        will_be_break[a][b]=1;
                    }
                }
            }
            flag=false;
            memset(visited, 0, sizeof(visited));
        }
    }
    delete_block();
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    string tmp;
    cin>>size_y>>rule;
    for(int i=0; i<size_y; i++)
    {
        cin>>tmp;
        for(int j=0; j<size_x; j++)
        {
            map[i][j]=tmp[j]-'0';
        }
    }
    while(!stop)
    solve();
    for(int a=0; a<size_y; a++)
    {
        for(int b=0; b<size_x; b++)
        {
            cout<<map[a][b];
        }
        cout<<"\n";
    }
}
