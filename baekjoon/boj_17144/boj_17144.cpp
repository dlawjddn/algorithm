#include <iostream>
#include <cstring>
using namespace std;
int map[51][51], temp_map[52][52], move_x[4]={1,0,-1,0}, move_y[4]={0,1,0,-1}, size_x=0, size_y=0, test=0, first_x=0, first_y=0, second_x=0, second_y=0, ans=0;
void cleaning_air()
{
    for(int a=1; a<size_x; a++) // 첫번째 아래 가로 순환, 두번째 위 가로 순환
    {
        if (a==second_x || a==first_x) continue;
        temp_map[first_y][a+1]=map[first_y][a];
        temp_map[second_y][a+1]=map[second_y][a];
    }
    for(int b=size_x; b>=2; b--) // 첫번째 위 가로 순환, 두번째 아래 가로 순환
    {
        temp_map[1][b-1]=map[1][b];
        temp_map[size_y][b-1]=map[size_y][b];
    }
    for(int c=1; c<size_y; c++) // 첫번째 왼쪽 세로 순환 두번째 오른 세로 순환
    {
        if (c<first_y)
            temp_map[c+1][first_x]=map[c][first_x];
        else if (c>=second_y)
            temp_map[c+1][size_x]=map[c][size_x];
        else continue;
    }
    for(int d=size_y; d>=2; d--)
    {
        if (d>second_y)
            temp_map[d-1][second_x]=map[d][second_x];
        else if (d<=first_y)
            temp_map[d-1][size_x]=map[d][size_x];
        else continue;
    }
    for(int q=1; q<=size_y; q++)
    {
        for(int w=1; w<=size_x; w++)
        {
            if (map[q][w]==-1) continue;
            else if ((q>1 && q<first_y) && (w>1 && w<size_x) || (q>second_y && q<size_y) && (w>1 && w<size_x)) continue;
            else
            map[q][w]=temp_map[q][w];
        }
    }
    memset(temp_map, 0, sizeof(temp_map));
}
void spread_dust()
{
    for(int y=1; y<=size_y; y++)
    {
        for(int x=1; x<=size_x; x++)
        {
            if (map[y][x]>0)
            {
                int cnt=0;
                for(int d=0; d<4; d++)
                {
                    int ny=y+move_y[d], nx=x+move_x[d];
                    if (ny>0 && ny<=size_y && nx>0 && nx<=size_x && map[ny][nx]!= -1)
                    {
                        temp_map[ny][nx]+=map[y][x]/5;
                        cnt++;
                    }
                }
                temp_map[y][x]=map[y][x]-((map[y][x]/5)*cnt)+temp_map[y][x];
            }
        }
    }
    for(int a=1; a<=size_y; a++)
    {
        for(int b=1; b<=size_x; b++)
        {
            if (map[a][b]==-1) continue;
            else
            map[a][b]=temp_map[a][b];
        }
    }
    memset(temp_map, 0, sizeof(temp_map));
}
int main()
{
    cin>>size_y>>size_x>>test;
    for(int i=1; i<=size_y; i++)
    {
        for(int j=1; j<=size_x; j++)
        {
            cin>>map[i][j];
            if (map[i][j]==-1)
            {
                if (first_x==0)
                {
                    first_x=j, first_y=i;
                }
                else
                {
                    second_x=j, second_y=i;
                }
            }
        }
    }
    for(int k=0; k<test; k++)
    {
        spread_dust();
        cleaning_air();
    }
    for(int a=1; a<=size_y; a++)
    {
        for(int b=1; b<=size_x; b++)
        {
            if (map[a][b]>0)
            ans+=map[a][b];
        }
    }
    cout<<ans;
}
