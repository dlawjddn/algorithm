#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
int map[1000][1000], visited[1000][1000], power[11], move_x[4]={1,0,-1,0}, move_y[4]={0,1,0,-1}, size_x=0, size_y=0, player=0;
int main(){
    cin>>size_y>>size_x>>player;
    for(int i=1; i<=player; i++) cin>>power[i];
    for(int a=0; a<size_y; a++){
        string str;
        cin>>str;
        for(int b=0; b<size_x; b++){
            if (str[b]=='.') map[a][b]=0;
            else if (str[b]>='0' && str[b]<='9') map[a][b]=str[b]-'0';
        }
    }
    for(int a=0; a<size_y; a++){
        for(int b=0; b<size_x; b++){
            cout<<map[a][b];
        }
        cout<<"\n";
    }
}
