#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

bool isprime(int num) {
    for(int i = 2; i*i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

string bfs(int src, int dest) {
    queue<pair<int, int> > q;
    vector<bool> visited(10000, false);
    q.push({src, 0});
    visited[src] = true;

    while(!q.empty()) {
        auto[num, cnt] = q.front(); q.pop();
        if (num == dest) {
            return to_string(cnt);
        }
        string str_num = to_string(num);
        for(int i=0; i<4; i++) {
            string temp = str_num;
            for(char a = '0'; a <= '9'; a++) {
                temp[i] = a;
                int nnum = stoi(temp);
                if (nnum < 1000 || visited[nnum] || !isprime(nnum)) continue;
                q.push({nnum, cnt+1});
                visited[nnum] = true;
            }
        }
    }
    return "Impossible";
}

int main() {
    int test_case; cin>>test_case;
    for(int t=0; t<test_case; t++) {
        int src, dest; cin>>src>>dest;
        cout<<bfs(src, dest)<<"\n";
    }
}