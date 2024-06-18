#include <iostream>
using namespace std;
int map[100][100], move_x[8]={1,1,0,-1,-1,-1,0,1}, move_y[8]={0,1,1,1,0,-1,-1,-1}, N=0, cnt=0;
int find_out()
{
    for(int y=1; y<N-1; y++)
    {
        for(int x=1; x<N-1; x++)
        {
            int check=0;
            for(int d=0; d<8; d++)
            {
                int ny=y+move_y[d];
                int nx=x+move_x[d];
                if (map[ny][nx]==0)
                {
                    check=1;
                    break;
                }
            }
            if (!check)
            {
                map[y][x]=9;
                for(int d=0; d<8; d++)
                {
                    int ny=y+move_y[d];
                    int nx=x+move_x[d];
                    if (map[ny][nx]>0 && map[ny][nx]<9)
                    map[ny][nx]-=1;
                }
                cnt++;
            }
        }
    }
    return cnt;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    string s;
    cin>>N;
    for(int i=0; i<N; i++)
    {
        cin>>s;
        for(int j=0; j<N; j++)
        {
            if (s[j]=='#')
            map[i][j]=-1;
            else
            map[i][j]=s[j]-'0';
        }
    }
    cout<<find_out();
}