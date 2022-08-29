#include <iostream>
#include <cmath>
using namespace std;
struct Point
{
    int x, y;
};
Point house[101], chicken[14];
int map[50][50], arr[14], N=0, num_h=1, num_c=1, lim=0, ans=987654321;
int check_dist(int temp1_y, int temp1_x, int temp2_y, int temp2_x)
{
    return abs(temp1_y-temp2_y)+abs(temp1_x-temp2_x);
}
void chicken_street()
{
    int temp_ans=0;
    for(int a=1; a<num_h; a++)
    {
        int temp_min=987654321;
        for(int b=1; b<=lim; b++)
        {
            temp_min=min(temp_min, check_dist(house[a].y, house[a].x, chicken[arr[b]].y, chicken[arr[b]].x));
        }
        temp_ans+=temp_min;
    }
    ans=min(ans, temp_ans);
}
void find_out(int idx, int num)
{
    if (idx==lim)
    {
        chicken_street();
        return;
    }
    else
    {
        idx++;
        for(int k=num+1; k<num_c; k++)
        {
            arr[idx]=k;
            num=k;
            find_out(idx, num);
        }
    }
}
void combination()
{
    for(int i=1; i<num_c; i++)
    {
        int idx=1, num=i;
        arr[idx]=num;
        find_out(idx, num);
    }
    cout<<ans;
}
int main()
{
    cin>>N>>lim;
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            cin>>map[i][j];
            if (map[i][j]==1)
            {
                house[num_h].y=i;
                house[num_h].x=j;
                num_h++;
            }
            else if (map[i][j]==2)
            {
                chicken[num_c].y=i;
                chicken[num_c].x=j;
                num_c++;
            }
        }
    }
    combination();
}