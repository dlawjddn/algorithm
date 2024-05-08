#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<bool>> map(5001, vector<bool>(5001, false));
vector<vector<char>> alpha(5001, vector<char>(5001, ' '));

int node_cnt = 0, line_cnt = 0, answer = 0;

void print_map(){
    for(int y=1; y<=node_cnt; y++){
        for(int x=1; x<=node_cnt; x++){
            cout<<map[y][x];
        }
        cout<<"\n";
    }
}

void print_alpha(){
    for(int y=1; y<=node_cnt; y++){
        for(int x=1; x<=node_cnt; x++){
            cout<<alpha[y][x];
        }
        cout<<"\n";
    }
}
void lcs(string dest, string str){
    vector<vector<int> > dp(dest.size()+1, vector<int>(str.size()+1, 0));
    //cout<<dest<<" "<<str<<"\n";
    for(int y=1; y<dest.size()+1; y++){
        for(int x=1; x<str.size()+1; x++){
            if (dest[y-1] == str[x-1]) dp[y][x] = dp[y-1][x-1] + 1;
            else dp[y][x] = max(dp[y-1][x], dp[y][x-1]);
        }
    }
    answer = max(answer, dp[dest.size()][str.size()]);
    
}

bool dfs(int num, string str, string dest, vector<int> visited){
    visited[num] = 1;
    bool last_flag = true;
    for(int x=1; x<=node_cnt; x++){
        if (visited[x] == 0 && map[num][x]){
            dfs(x, str+alpha[num][x], dest, visited);
            last_flag = false;
        }
    }
    if (last_flag) {
        lcs(dest, str);
    }
}

int main(int argc, char** argv)
{
    string dest;
    cin>>node_cnt>>line_cnt;
    cin>>dest;
    for(int i=0; i<line_cnt; i++){
        int node1 = 0, node2 = 0;
        char value;
        cin>>node1>>node2>>value;
        map[node1][node2] = true;
        map[node2][node1] = true;
        alpha[node1][node2] = value;
        alpha[node2][node1] = value;
    }
    vector<int> visited(node_cnt+1, 0);
    dfs(1, "", dest, visited);
    cout<<answer;
}