#include <iostream>
#include <queue>
#include <cmath>
using namespace std;
queue<pair<int , int> > q, w;
int cnt_a[20][500001], cnt_b[20][500001], size_arr=0, pos_a=0, pos_b=0;
int use_bfs()
{
    cnt_a[0][pos_a]=1; cnt_b[0][pos_b]=1;
    q.push(make_pair(1, pos_a));
    w.push(make_pair(1, pos_b));
    while(!q.empty())
    {
        int day=q.front().first, pos=q.front().second; q.pop();
        for(int d=0; d<2; d++)
        {
            int n_pos=0;
            if (d==0) n_pos=pos+(int)pow(2, day-1);
            else n_pos=pos-(int)pow(2, day-1);
            if (n_pos>0 && n_pos<=size_arr)
            {
                cnt_a[day][n_pos]=1;
                q.push(make_pair(day+1, n_pos));
            }
        }
    }
    while(!w.empty())
    {
        int day=w.front().first, pos=w.front().second; w.pop();
        for(int d=0; d<2; d++)
        {
            int n_pos=0;
            if (d==0) n_pos=pos+(int)pow(2, day-1);
            else n_pos=pos-(int)pow(2, day-1);
            if (n_pos>0 && n_pos<=size_arr)
            {
                cnt_b[day][n_pos]=1;
                w.push(make_pair(day+1, n_pos));
            }
        }
    }
    for(int day=0; day<20; day++)
    {
        for(int pos=1; pos<=size_arr; pos++)
        {
            if (cnt_a[day][pos]==1 && cnt_b[day][pos]==1) return day;
        }
    }
    return -1;
}
int main()
{
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>size_arr>>pos_a>>pos_b;
    cout<<use_bfs();
}