#include <iostream>
#include <queue>
#include <algorithm>
#include <set>
#include <string>
using namespace std;
int move_y[4]={0,1,0,-1}, move_x[4]={1,0,-1,0};
string start, dest;
set<string> visited;
int use_bfs(){
    queue<pair<string, int> > q;
    q.push(make_pair(start, 0));
    visited.insert(start);
    while(!q.empty()){
        string temp = q.front().first;
        int cnt=q.front().second; q.pop();
        if (temp == dest) return cnt;
        int zero=temp.find('0');
        int y=zero/3;
        int x=zero%3;
        for(int d=0; d<4; d++){
            int ny=y+move_y[d];
            int nx=x+move_x[d];
            if (ny>=0 && ny<3 && nx>=0 && nx<3){
                string next=temp;
                swap(next[y*3+x], next[ny*3+nx]);
                if (visited.find(next)==visited.end()){
                    visited.insert(next);
                    q.push(make_pair(next, cnt+1));
                }
            }
        }
    }
    return -1;
}
int main(){
    dest="123456780";
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            int temp=0;
            cin>>temp;
            start+=temp+'0';
        }
    }
    cout<<use_bfs();
}