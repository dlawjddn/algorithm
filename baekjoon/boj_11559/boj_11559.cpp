#include <iostream>
#include <cstring>
using namespace std;
char map[12][6];
bool flag=false, stop=false;
int visited[12][6], will_be_break[12][6], move_x[4]={1,0,-1,0}, move_y[4]={0,1,0,-1}, ans=0, cnt=0;
void get_low()
{
    for(int x=0; x<6; x++)
    {
        int empty_cnt=0;
        for(int y=11; y>=0; y--)
        {
            if (map[y][x]=='.')
            empty_cnt++;
            else if (map[y][x]!='.' && empty_cnt!=0)
            {
                map[y+empty_cnt][x]=map[y][x];
                map[y][x]='.';
            }
            else if (map[y][x]!='.' && empty_cnt==0)
            continue;
        }
    }
}
void doit_puyo()
{
    int check=0;
    for(int a=0; a<12; a++)
    {
        for(int b=0; b<6; b++)
        {
            if (will_be_break[a][b]==1)
            {
                map[a][b]='.';
                check++;
            }
        }
    }
    memset(will_be_break, 0, sizeof(will_be_break));
    if (!check)
    stop=true;
    get_low();
}
void use_dfs(int y, int x)
{
    cnt++;
    visited[y][x]=1;
    if (cnt>=4)
        flag=true;
    for(int d=0; d<4; d++)
    {
        int ny=y+move_y[d], nx=x+move_x[d];
        if (ny>=0 && ny<12 && nx>=0 && nx<6 && visited[ny][nx]==0 && map[y][x]==map[ny][nx])
        use_dfs(ny, nx);
    }
}
void puyo_puyo()
{
    for(int a=11; a>=0; a--)
    {
        for(int b=0; b<6; b++)
        {
            cnt=0;
            if (map[a][b]!='.' && visited[a][b]==0)
            {
                use_dfs(a, b);
                if (flag)
                {
                    for(int q=0; q<12; q++)
                    {
                        for(int w=0; w<6; w++)
                        {
                            if (visited[q][w]==1)
                            will_be_break[q][w]=1;
                        }
                    }
                }
                memset(visited, 0, sizeof(visited));
            }
            flag=false;
        }
    }
    doit_puyo();
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    string tmp;
    for(int i=0; i<12; i++)
    {
        cin>>tmp;
        for(int j=0; j<6; j++)
        {
            map[i][j]=tmp[j];
        }
    }
    while(!stop)
    {
        puyo_puyo();
        if (!stop)
        ans++;
    }
    cout<<ans;
}