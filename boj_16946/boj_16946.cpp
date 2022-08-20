#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
char map[1001][1001];
bool visited[1000][1000];
int ans[1000][1000], group[5000001], move_x[4]={1,0,-1,0}, move_y[4]={0,1,0,-1}, size_y=0, size_x=0, group_size=0;
queue<pair<int , int> >  q;
void last_part()
{
    while(!q.empty())
    {
        int temp_num[4], sum=1;
        int y=q.front().first;
        int x=q.front().second; q.pop();
        for(int d=0; d<4; d++)
        {
            int ny=y+move_y[d], nx=x+move_x[d];
            if (ny>=0 && ny<size_y && nx>=0 && nx<size_x && map[ny][nx]=='0' && ans[ny][nx]>0)
                temp_num[d]=ans[ny][nx];
            else
                temp_num[d]=0;
        }
        for(int a=1; a<4; a++)
        {
            for(int b=0; b<a; b++)
            {
                if (temp_num[b]==temp_num[a])
                {
                    temp_num[a]=0;
                    break;
                }
            }
        }
        for(int k=0; k<4; k++)
        sum+=group[temp_num[k]]%10;
        ans[y][x]=sum%10;
    }
}
void use_dfs(int y, int x, int cnt)
{
    visited[y][x]=true;
    ans[y][x]=cnt;
    group_size++;
    for(int d=0; d<4; d++)
    {
        int ny=y+move_y[d], nx=x+move_x[d];
        if (ny>=0 && ny<size_y && nx>=0 && nx<size_x && visited[ny][nx]==false && map[ny][nx]=='0')
        use_dfs(ny, nx, cnt);
    }
}
void checking_group()
{
    int cnt=0;
    for(int a=0; a<size_y; a++)
    {
        for(int b=0; b<size_x; b++)
        {
            if (map[a][b]=='0' && visited[a][b]==false)
            {
                cnt++;
                use_dfs(a, b, cnt);
                group[cnt]=group_size;
                group_size=0;
            }
        }
    }
}
int main()
{
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    string tmp;
    cin>>size_y>>size_x;
    for(int i=0; i<size_y; i++)
    {
        cin>>tmp;
        for(int j=0; j<size_x; j++)
        {
            map[i][j]=tmp[j];
            if (map[i][j]=='1')
            q.push(make_pair(i, j));
        }
    }
    checking_group();
    last_part();
    for(int q=0; q<size_y; q++)
    {
        for(int w=0; w<size_x; w++)
        {
            if (map[q][w]=='1')
            cout<<ans[q][w]%10;
            else
            cout<<"0";
        }
        cout<<"\n";
    }
}