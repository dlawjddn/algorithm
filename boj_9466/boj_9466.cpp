#include <iostream>
#include <cstring>
using namespace std;
int testCase=0, len=0, want[100001], cnt=0;
bool visited[100001], finish[100001];
void dfs(int num){
    visited[num]=true;
    int next =  want[num];
    if (!visited[next]) dfs(next);
    else if (!finish[next]){
        for(int i=next; i!=num; i=want[i]) cnt++;
        cnt++;
    }
    finish[num]=true;
}
int main(){
    cin>>testCase;
    for(int i=0; i<testCase; i++){
        cin>>len;
        cnt=0;
        memset(visited, 0, sizeof(visited));
        memset(finish, 0, sizeof(finish));
        for(int k=1; k<=len; k++){
            cin>>want[k];
        }
        for(int j=1; j<=len; j++){
            if (!visited[j]) dfs(j);
        }
        cout<<len-cnt<<"\n";
    }
}